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




int not(int input) {
    if(input == 0) {
        return 1;
    } else {
        return 0;
    }
}







char *game_name() {
    return "Judge";
}