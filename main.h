//
// Created by dando on 17/08/2022.
//

#ifndef DAVIDE_FLORE_66174_MAIN_H
#define DAVIDE_FLORE_66174_MAIN_H

#endif //DAVIDE_FLORE_66174_MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "letters.h"


#define PAGE_SIZE 25


typedef struct {
    int index;
    char nome[64];
    int spr1d_game_giocati;
    int spr1d_game_vinti;
    int finali_giocate;
    int giochi_giocati;
    int giochi_vinti;
} ProfiloGiocatore;


typedef struct {
    int id;
    bool vivo;
    ProfiloGiocatore *p;
} Elenco;








int potenza(int x, int y) {

    int r = x;

    if(y == 0) {
        return 1;
    } else {
        for(int i = 1; i < y; i++) {
            r *= x;
        }
        return r;
    }
}








bool is_numeric(char *num) {



    for(int i = 0; i < strlen(num); i++) {
        if((int)num[i] < 48 || (int)num[i] > 57) {
            return false;
        }
    }

    return true;
}








int string_to_int(char *str) {

    int k, p, total = 0;

    //itera per la stringa da destra verso sinistra escludendo il carattere di fine stringa
    for(k = (int)strlen(str) - 1, p = 0; k >= 0; k--, p++) {

        //calcola il calore di ogni cifra e lo aggiunde al risultato
        total += ((int) str[k] - 48) * potenza(10, p);
    }

    return total;
}





int get_int(char *query, int min, int max) {

    char num[4];
    int number = 0;
    bool check = true;

    do {
        //pone la domanda e raccoglie la risposta sotto forma di stringa
        printf("%s", query);
        scanf(" %s", num);

        //controlla che la stringa sia numerica con una funzione apposita
        if(is_numeric(num) == true) {
            //se lo è, la converte in un intero con una funzione apposita
            number = string_to_int(num);
            check = true;
            //poi controlla che sia incluso nell'intervallo
            if(number < min) {
                printf("\nIl numero deve essere maggiore di o uguale a %d\n", min);
                printf("Dai, ritenta...\n\n");
                check = false;
            } else if(number > max) {
                printf("\nIl numero deve essere maggiore di o uguale a %d\n", max);
                printf("Dai, ritenta...\n\n");
                check = false;
            }
        } else {
            printf("\nnon numero!!\nRitenta...\n\n");
            check = false;
        }
        //in ogni altro caso ripete il loop
    } while(check == false);

    return number;
}





int choice_string(char *query, int num, char options[num][10]) {

    int answer = num + 2;
    bool check = true;

    char choice[20];

    do {
        check = true;
        printf("%s", query);
        scanf(" %s", choice);

        for(int i = 0; i < num; i++) {
            if(strcmp(choice, options[i]) == 0) {
                answer = i;
            }
        }
        if(answer > num) {
            printf("\nSBAGLIATO! Scegli una delle opzioni!");
            check = false;
        }
    } while(check == false);

    return answer;
}


int si_no(char *query) {

    char si_o_no[2][10] = {"no", "si"};

    return choice_string(&query[0], 2, si_o_no);
}






bool is_player(Elenco player) {
    if(player.p == NULL) {
        return false;
    } else {
        return true;
    }
}





int rand_int(int min, int max) {
    return (rand() % (max - min + 1)) + min;
}




char *print_player(Elenco player) {

    char *ret = calloc(14, sizeof(char));

    //riscrivere da zero
    if(player.p != NULL) {
        return player.p->nome;
    } else {
        if(player.id >= 0) {
            // converti in stringa
            int powers[3] = {100, 10, 1};
            int num = player.id;
            strcpy(ret, "Giocatore \0");
            for(int i = 0; i < 3; i++) {
                ret[i + 10] = (char)((num / powers[i]) + 48);
                //printf("%d", num / powers[i]);
                num %= powers[i];
            }
            ret[14] = '\0';
        }

        return ret;
    }
}






Elenco *componi_elenco(int numero_giocatori) {

    int i;
    Elenco *players = NULL;

    players = (Elenco *) calloc(numero_giocatori, sizeof(Elenco));
    if(players == NULL) {
        printf("\n\nERRORE! Allocazione fallita!\n\n");
        exit(-1);
    }

    for(i = 0; i < numero_giocatori; i++) {
        players[i].id = i;
        players[i].p = NULL;
        players[i].vivo = true;
    }

    return players;
}










void stampa(Elenco **groups, int size, int start, int finish) {

    printf("\n");
    for(int j = 0; j <= size; j++) {
        for(int k = start; k < finish; k++) {

            if(is_player(groups[k][j])) {
                if(strlen(groups[k][j].p->nome) >= 21) {
                    for(int d = 0; d <= 21; d++) {
                        printf("%c", groups[k][j].p->nome[d]);
                    }
                    printf(" ");
                } else {
                    printf("%s", groups[k][j].p->nome);
                    for(int t = 0; t < 22 - strlen(groups[k][j].p->nome); t++) {
                        printf(" ");
                    }
                }
            } else {
                print_player(groups[k][j]);
                printf("         ");
            }

        }
        printf("\n");
    }
}



void stampa_gruppetti(Elenco **groups, int target, int size, int width) {

    int i = 0, segnaposto = 0;
    int width_save = width;


    while(i < target) {
        if(i != 0 && i % width == 0) {

            // stampa i gruppetti da segnaposto a width
            stampa(&groups[0], size, segnaposto, width);

            segnaposto = width;
            width += width_save;

            printf("\n\n");
        }
        printf("%do gruppo:          ", i + 1);
        if(i < 9) {
            printf("  ");
        } else if(i < 99) {
            printf(" ");
        }

        i++;
    }
    stampa(&groups[0], size, segnaposto, target);
}







char *game_name() {
    return "Judge";
}