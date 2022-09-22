//
// Created by dando on 21/09/2022.
//

#ifndef DAVIDE_FLORE_66174_MURRA_H
#define DAVIDE_FLORE_66174_MURRA_H

#endif //DAVIDE_FLORE_66174_MURRA_H


#include "tris.h"


int murra(Elenco *);
void layout_murra(Elenco *, int, int[2]);






int murra(Elenco *giocatori) {

    int i;

    int scelta[2] = {0, 0};
    int somma[2];

    do {
        scelta[0] = scelta[1] = 0;

        // turni
        for(i = 0; i < 2; i++) {

            layout_murra(&giocatori[0], i, scelta);

            if(is_player(giocatori[i])) {
                printf("\n[%s]: Inserisci il numero di dita che vuoi buttare e un pronostico della somma", game_name());
                printf("\n[%s]: Dita:\n[%s]: ", game_name(), print_player(giocatori[i]));
                scelta[i] = get_int("", 1, 5);
                getchar();

                printf("\n[%s]: Somma:\n[%s]: ", game_name(), print_player(giocatori[i]));
                somma[i] = get_int("", 2, 10);
                getchar();
            } else {

                // numeri del computer
                // la somma è sempre maggiore di o uguale al numero
                scelta[i] = rand_int(1, 5);
                somma[i] = rand_int(scelta[i], 10);

                printf("\n[%s]: Inserisci il numero che vuoi buttare e la somma", game_name());
                printf("\n[%s]: Butto %d dita e %d come somma!", print_player(giocatori[i]), scelta[i], somma[i]);
                getchar();
            }
        }

        // controlla pareggio
        if(somma[0] == somma[1] == scelta[0] + scelta[1]) {
            // stampa layout pareggio
            layout_murra(giocatori, 3, scelta);

            printf("\n[%s]: Sembra che la partita si sia conclusa in pareggio! Riproviamo!", game_name());
            getchar();
        } else if(somma[0] == scelta[0] + scelta[1]) {
            // stampa layout vittoria primo giocatore
            getchar();

            return 0;
        } else if(somma[1] == scelta[0] + scelta[1]) {
            // stampa layout vittoria secondo giocatore
            getchar();

            return 1;
        } else {
            // stampa layout fiasco
            layout_murra(giocatori, 3, scelta);

            printf("\n[%s]: Nessuno dei due ha avuto fortuna! Riproviamo!", game_name());
            getchar();
        }


    } while(true);
}







void layout_murra(Elenco *giocatori, int turno, int numeri[2]) {

    // 3 righe occupate
    printf("--------[STAI GIOCANDO A MURRA]--------\n\n");

    // stampa le dita
    printf("[%s] HA BUTTATO:       [%s] HA BUTTATO:\n", print_player(giocatori[0]), print_player(giocatori[1]));
    print_num(numeri, 2);



    // 5 righe occupate
    if(turno >= 2) {
        //
        printf("\n\n\nVittoria!!!\n\n\n\n");

    } else {
        printf("\n\n");
        stampa_turno(&giocatori[0], 2, turno);
    }
    printf("\n\n\n");

}
