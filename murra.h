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


    // itera per la partita, fino alla vittoria di uno dei due giocatori
    do {
        // azzera le scelte ogni volta
        scelta[0] = 0;
        scelta[1] = 0;

        // itera di nuovo per alternare i turni
        for(i = 0; i < 2; i++) {

            // se il giocatore di turno è un utente, il programma prende la scelta corrispondente tramire get-int()
            if(is_player(giocatori[i])) {
                printf("\n[%s]: Inserisci il numero di dita che vuoi buttare e un pronostico della somma", game_name());
                printf("\n[%s]: Dita:\n[%s]: ", game_name(), print_player(giocatori[i]));
                scelta[i] = get_int("", 1, 5);
                getchar();

                // prende anche il pronostico della somma con lo stesso metodo
                printf("\n[%s]: Somma:\n[%s]: ", game_name(), print_player(giocatori[i]));
                somma[i] = get_int("", 2, 10);
                getchar();
            } else {

                // altrimenti sceglie il numero a caso
                // si premura inoltre che la somma sia sempre maggiore della scelta
                scelta[i] = rand_int(1, 5);
                somma[i] = rand_int(scelta[i] + 1, 10);

                printf("\n[%s]: Inserisci il numero che vuoi buttare e la somma", game_name());
                printf("\n[%s]: Butto %d dita e %d come somma!", print_player(giocatori[i]), scelta[i], somma[i]);
                getchar();
            }
        }

        // presi tutti i valori, li controlla per decidere la vittoria o i lpareggio
        if(somma[0] == somma[1] == scelta[0] + scelta[1]) {
            // se entrambi hanno azzeccato la somma giusta, stampa un messaggio di pareggio e continua il ciclo
            printf("\n%s: %d dita, %d di somma", print_player(coppia[0]), scelta[0], somma[0]);
            printf("\n%s: %d dita, %d di somma", print_player(coppia[1]), scelta[1], somma[1]);
            printf("\n\n\n[%s]: Sembra che la partita si sia conclusa in pareggio! Riproviamo!", game_name());
            getchar();
        } else if(somma[0] == scelta[0] + scelta[1]) {
            // se invece solo il primo giocatore ha buttato la somma giusta, la funzione ritorna 0
            printf("\n[%s]: %s ha azzeccato la somma giusta!", game_name(), print_player(coppia[0]));
            getchar();
            return 0;
        } else if(somma[1] == scelta[0] + scelta[1]) {
            // se solo il secondo ha indovinato, la funzione ritorna 1
            printf("\n[%s]: %s ha azzeccato la somma giusta!", game_name(), print_player(coppia[1]));
            getchar();
            return 1;
        } else {
            // se invece non ci ha preso nessuno, il ciclo si ripete
            printf("\n[%s]: Nessuno dei due ha avuto fortuna! Riproviamo!", game_name());
            getchar();
        }
    } while(true);
}
