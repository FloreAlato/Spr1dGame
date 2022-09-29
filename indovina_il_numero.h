//
// Created by Dando on 9/23/2022.
//

#ifndef DAVIDE_FLORE_66174_INDOVINA_IL_NUMERO_H
#define DAVIDE_FLORE_66174_INDOVINA_IL_NUMERO_H

#endif //DAVIDE_FLORE_66174_INDOVINA_IL_NUMERO_H


#include "morra_cinese.h"




int indovina_il_numero(Elenco *, int);
void layout_indovina(Elenco *, int, int, int, int, char *);










// funzione layout per il gioco indovina_il_numero()
// prende l'Elenco dei giocatori in partita, il loro numero e altre informazioni per il layout
// stampa semplicemente la schermata che si vede giocando a indovina_il_numero()
void layout_indovina(Elenco *players, int dim, int turno, int min, int max, char *count) {

    int i;

    // 4 righe occupate
    printf("--------[STAI GIOCANDO A INDOVINA IL NUMERO]--------\n\n\n");

    // 7 righe occupate
    printf("[000]%s[999]\n", count);
    printf("[%d < X < %d]\n\n\n\n\n", min, max);

    // differenzia fra schermata normale e schermata di vittoria
    // usa i turni per orientarsi, quindi la schermata di vittoria non riporta il turno corrente
    if(turno <= numero_giocatori) {
        stampa_turno(players, dim, turno);
        for(i = 16; i < PAGE_SIZE - 3; i++) {
            printf("\n");
        }
    } else {
        printf("\n\n\n\n\nFINE GIOCO!!!!\n\n\n\n\n\n\n\n\n\n[%s]: Premi invio per continuare (invio)", game_name());
    }
}








// gioco di indovina_il_numero()
// prende una coppia di giocatori e la sua dimensione e restituisce l'indice del vincitore nella coppia stessa
int indovina_il_numero(Elenco *players, int dim) {

    int numero, min, max, scelta, i;

    // inizializza e riempie la stringa che conterrà le indicazioni per il layout
    char count[101];
    for(i = 0; i < 100; i++) {
        count[i] = '.';
    }
    count[100] = '\0';


    // stabilisce un range standard e sceglie il numero a caso
    min = 0;
    max = 999;

    numero = rand_int(min, max);


    // loop partita
    while(true) {

        // itera fra i (2) giocatori
        for(i = 0; i < dim; i++) {

            // stampa il layout e chiede all'utente il numero da indovinare
            layout_indovina(players, dim, i, min, max, count);
            printf("\n\n\n\n\n[%s]: Indovina il numero\n[%s]", game_name(), print_player(players[i]));

            // se il giocatore è utente, prende il numero in input, altrimenti lo sceglie a caso nel range del numero da indovinare
            if(is_player(players[i])) {
                scelta = get_int(": ", 0, 999);
                getchar();
            } else {
                scelta = rand_int(min + 1, max - 1);
                printf(": %d", scelta);
                getchar();
            }

            // controlla il numero scelto e da indicazioni all'utente / programma per aiutarlo nella scelta
            // restringe il campo ad ogni errore così che la CPU diventi man mano più precisa e difficile da battere (funziona)
            if(scelta > numero) {
                printf("\n[%s]: Troppo alto!", game_name());
                max = scelta;
                count[scelta / 10] = 'A';
                getchar();
            } else if(scelta < numero) {
                printf("\n[%s]: Troppo basso!", game_name());
                min = scelta;
                count[scelta / 10] = 'B';
                getchar();
            } else {
                // se il nuemro viene indovinato, stampa il layout della vittoria
                // ovvero sempre layout_indovina(), ma con un turno che non esiste
                // infine ritorna l'indice del vincitore
                count[scelta / 10] = 'X';
                layout_indovina(players, dim, dim + 1, min, max, count);
                getchar();
                return i;
            }
        }
    }
}





