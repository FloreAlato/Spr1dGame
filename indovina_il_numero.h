//
// Created by Dando on 9/23/2022.
//

#ifndef DAVIDE_FLORE_66174_INDOVINA_IL_NUMERO_H
#define DAVIDE_FLORE_66174_INDOVINA_IL_NUMERO_H

#endif //DAVIDE_FLORE_66174_INDOVINA_IL_NUMERO_H


#include "murra.h"




int indovina_il_numero(Elenco *, int);
void layout_indovina(Elenco *, int, int, int, int, char *);











void layout_indovina(Elenco *giocatori, int numero_giocatori, int turno, int min, int max, char *count) {

    int i;

    // 4 righe occupate
    printf("--------[STAI GIOCANDO A INDOVINA IL NUMERO]--------\n\n\n");

    // 7 righe occupate
    printf("[000]%s[999]\n", count);
    printf("[%d < X < %d]\n\n\n\n\n", min, max);

    // 5 righe occupate
    if(turno <= numero_giocatori) {
        stampa_turno(giocatori, numero_giocatori, turno);
        for(i = 16; i < PAGE_SIZE - 3; i++) {
            printf("\n");
        }
    } else {
        printf("\n\n\n\n\nFINE GIOCO!!!!\n\n\n\n\n\n\n\n\n\n[%s]: Premi invio per continuare (invio)", game_name());
    }
}









int indovina_il_numero(Elenco *giocatori, int numero_giocatori) {

    int numero, min, max, scelta, i;

    char count[101];
    for(i = 0; i < 100; i++) {
        count[i] = '.';
    }
    count[100] = '\0';


    min = 0;
    max = 999;

    numero = rand_int(min, max);


    // loop partita
    while(true) {

        // loop giocatori
        for(i = 0; i < numero_giocatori; i++) {

            // stampa il layout e chiedi il numero
            layout_indovina(giocatori, numero_giocatori, i, min, max, count);
            printf("\n\n\n\n\n[%s]: Indovina il numero\n[%s]", game_name(), print_player(giocatori[i]));

            // ottieni il numero
            if(is_player(giocatori[i])) {
                scelta = get_int(": ", 0, 999);
                getchar();
            } else {
                scelta = rand_int(min + 1, max - 1);
                printf(": %d", scelta);
                getchar();
            }

            // controlla il numero e cambia i fattori
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
                // stampa layout vittoria
                count[scelta / 10] = 'X';
                layout_indovina(giocatori, numero_giocatori, numero_giocatori + 1, min, max, count);
                getchar();
                return i;
            }
        }
    }
}





