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


// dimensione pagina, per i layout
#define PAGE_SIZE 25

// struttura ProfiloGiocatore
typedef struct {
    int index;
    char nome[64];
    int spr1d_game_giocati;
    int spr1d_game_vinti;
    int finali_giocate;
    int giochi_giocati;
    int giochi_vinti;
} ProfiloGiocatore;

// struttura Elenco, per semplicità
typedef struct {
    int id;
    bool vivo;
    ProfiloGiocatore *p;
} Elenco;




// variabili condivise fra tutti i file .h
int numero_giocatori = 0, numero_giocatori_veri = 0, superstiti_scrematura = 0;
Elenco *giocatori = NULL;
ProfiloGiocatore *giocatori_veri;

char nome_utente[32] = "Tu";






// calcola la potenxa di x elevato y
// serve solo al suo scopo, pessima come funzione potenza generale
// se y vale 0, ritorna 0, altrimenti fa la potenza con la forza bruta
// l'ho scritta perchè a volte la funzione potenza della libreria matematica mi da un warning
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





// funzione che controlla se una string contiene solo caratteri numerici
// prende una stringa e restituisce un intero
bool is_numeric(char *num) {

    // itera fra i caratteri e controlla dove sono nell'ordine ascii
    for(int i = 0; i < strlen(num); i++) {
        if((int)num[i] < 48 || (int)num[i] > 57) {
            return false;
        }
    }

    return true;
}







// prende una stringa e restituisce un intero
int string_to_int(char *str) {

    int k, p, total = 0;

    //itera per la stringa da destra verso sinistra escludendo il carattere di fine stringa
    for(k = (int)strlen(str) - 1, p = 0; k >= 0; k--, p++) {

        //calcola il calore di ogni cifra e lo aggiunde al risultato
        total += ((int) str[k] - 48) * potenza(10, p);
    }

    // restituisce l'intero corrispondente
    return total;
}




// raccoglie un intero dall'utente entro un range, e fa il debug fuori dal range
// prende una stringa e due interi e restituisce un intero
int get_int(char *query, int min, int max) {

    char num[4];
    int number = 0;
    bool check = true;

    do {
        //pone la domanda e raccoglie la risposta sotto forma di stringa
        printf("%s", query);
        scanf(" %s", num);

        //controlla che la stringa sia numerica con is_numeric()
        if(is_numeric(num) == true) {
            //se lo è, la converte in un intero con string_to_int()
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
            printf("\nNon numero!!\nRitenta...\n\n");
            check = false;
        }
        //in ogni altro caso ripete il loop
    } while(check == false);

    // poi ritorna il numero ottenuto
    return number;
}




// choice string prende un intero in input facendo scegliere all'utente una fra le opzioni disponibili
// prende una stringa, il numero delle opzioni, un array di opzioni e restituisce un intero
int choice_string(char *query, int num, char options[num][10]) {

    int answer = num + 2;
    bool check = true;

    char choice[20];

    do {
        // stampa la domanda e prende la risposta
        check = true;
        printf("%s", query);
        scanf(" %s", choice);

        // se corrisponde a una delle opzioni, si segna il risultato
        for(int i = 0; i < num; i++) {
            if(strcmp(choice, options[i]) == 0) {
                answer = i;
            }
        }
        // altrimenti ripete il loop
        if(answer > num) {
            printf("\nSBAGLIATO! Scegli una delle opzioni!");
            check = false;
        }
    } while(check == false);

    // poi ritorna il risultato
    return answer;
}




// variante di choice_string() ma con solo due opzioni e meno parametri
// per semplicità di scrittura
int si_no(char *query) {

    char si_o_no[2][10] = {"no", "si"};

    return choice_string(&query[0], 2, si_o_no);
}





// controlla che un Elenco sia collegato a un utente e ritorna true, false altrimenti
bool is_player(Elenco player) {
    if(player.p == NULL) {
        return false;
    } else {
        return true;
    }
}




// è letteralmente rand() in un range, serve per non scrivere la formula ogni volta e per evitare i warnings di clion
int rand_int(int min, int max) {
    return (rand() % (max - min + 1)) + min;
}



// ritorna uno a caso fra i due proposti
int rand_int_between(int num1, int num2) {

    // prende un numero a caso fra i due e ritorna l'estremo più vicino
    int mid = rand_int(num1, num2);

    if(num2 - mid > mid - num1) {
        return num1;
    } else {
        return num2;
    }
}



// se un Elenco è utente ritorna il nome, altrimenti ritorna il numero del giocatore sotto forma di stringa
// prende un Elenco e restituisce una stringa
// per estetica e semplicità
char *print_player(Elenco player) {

    char *ret = calloc(14, sizeof(char));

    // se ha un profilo, restituisce il nome
    if(player.p != NULL) {
        return player.p->nome;
    } else {
        if(player.id >= 0) {
            // altrimenti converte l'id in stringa e ci mette "Giocatore " davanti
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




// componi elenco alloca e riempie un Elenco di giocatori
// prende un intero e restituisce un array di Elenco
Elenco *componi_elenco(int dim) {

    int i;
    Elenco *players = NULL;

    // alloca l'Elenco
    players = (Elenco *) calloc(dim, sizeof(Elenco));
    if(players == NULL) {
        printf("\n\nERRORE! Allocazione fallita!\n\n");
        exit(-1);
    }

    // riempie gli id progressivamente, i profili a NULL, e lo stato vitale a true
    for(i = 0; i < dim; i++) {
        players[i].id = i;
        players[i].p = NULL;
        players[i].vivo = true;
    }

    // ritorna l'array
    return players;
}



// controlla se un Elenco è Scateni
// prende un Elenco e restituisce un booleano
bool frontman(Elenco giocatore) {

    // controlla prima che si aun giocatore, e poi che il suo nome sia Riccardo Scateni
    if(is_player(giocatore) && strcmp(giocatore.p->nome, "Riccardo Scateni") == 0) {
        return true;
    }

    return false;
}




// controlla quanti giocatori sono vivi in un Elenco
// prende un Elenco, la sua dimensione e un puntatore a una coppia di interi
void superstiti(Elenco *gruppo, int dim, int *valori) {

    int i;

    // salva nei due interi il numero di giocatori vivi
    // e il numero di giocatori utente vivi
    for(i = 0; i < dim; i++) {
        if(gruppo[i].vivo) {
            valori[0]++;
        }
        if(gruppo[i].vivo && is_player(gruppo[i])) {
            valori[1]++;
        }
    }
}




// riempie un array di Elenco con i giocatori vivi di un altro Elenco
// prende un puntatore a Elenco e due interi
void solo_vivi(Elenco *destinazione, int totali, int vivi) {

    int i = 0, counter = 0;

    // itera fra l'Elenco lordo e riempie quello netto con tutti i vivi che trova fino a finirli o finire l'Elenco
    while(i < totali || counter < vivi) {

        if(giocatori[i].vivo) {
            destinazione[counter] = giocatori[i];
            counter++;
        }

        i++;
    }
}




// ritorna il nome del programma
// hehe
char *game_name() {
    return "Judge";
}

