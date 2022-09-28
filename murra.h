//
// Created by dando on 21/09/2022.
//

#ifndef DAVIDE_FLORE_66174_MURRA_H
#define DAVIDE_FLORE_66174_MURRA_H

#endif //DAVIDE_FLORE_66174_MURRA_H


#include "tris.h"






// gioco della murra
// prende in input una coppia e restituisce l'indice del vincitore nella coppia stessa
int murra(Elenco *coppia) {

    int i;

    int scelta[2] = {0, 0};
    int somma[2];


    // stampa un messaggio di inizio gioco
    printf("[%s]: GIOCHIAMO A MURRA!!!\n\n\n", game_name());


    do {
        scelta[0] = 0;
        scelta[1] = 0;

        // turni
        for(i = 0; i < 2; i++) {

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
                somma[i] = rand_int(scelta[i] + 1, 10);

                printf("\n[%s]: Inserisci il numero che vuoi buttare e la somma", game_name());
                printf("\n[%s]: Butto %d dita e %d come somma!", print_player(giocatori[i]), scelta[i], somma[i]);
                getchar();
            }
        }

        // controlla pareggio
        if(somma[0] == somma[1] == scelta[0] + scelta[1]) {
            // stampa layout pareggio
            printf("\n%s: %d dita, %d di somma", print_player(coppia[0]), scelta[0], somma[0]);
            printf("\n%s: %d dita, %d di somma", print_player(coppia[1]), scelta[1], somma[1]);

            printf("\n[%s]: Sembra che la partita si sia conclusa in pareggio! Riproviamo!", game_name());
            getchar();
        } else if(somma[0] == scelta[0] + scelta[1]) {

            printf("\n[%s]: %s ha azzeccato la somma giusta!", game_name(), print_player(coppia[0]));
            getchar();

            return 0;
        } else if(somma[1] == scelta[0] + scelta[1]) {

            printf("\n[%s]: %s ha azzeccato la somma giusta!", game_name(), print_player(coppia[1]));
            getchar();

            return 1;
        } else {

            printf("\n[%s]: Nessuno dei due ha avuto fortuna! Riproviamo!", game_name());
            getchar();
        }


    } while(true);
}
