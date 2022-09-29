//
// Created by Dando on 9/28/2022.
//

#ifndef DAVIDE_FLORE_66174_DADI_H
#define DAVIDE_FLORE_66174_DADI_H

#endif //DAVIDE_FLORE_66174_DADI_H



#include "murra.h"




// gioco dadi
// prende una coppia di Elenco e restituisce un intero
int dadi(Elenco *coppia) {

    // salva i punteggi correnti e precedenti
    int punteggio[2];
    int precedente[2] = {0, 0};

    printf("\n\n\n\n\n[%s]: Stai giocando a Dadi!!\n\n", game_name());

    while(true) {

        // turno 1
        // non imports che i giocatori siano utenti o meno, devono solo tirare i dadi
        printf("\n[%s]: Tira i dadi, %s (invio)", game_name(), print_player(coppia[0]));
        getchar();

        // il punteggio viene incrementato randomicamente
        // di 6 in 6, come se fossero 2 dadi
        punteggio[0] = rand_int(1, 6);
        punteggio[0] += rand_int(1, 6);
        printf("\n[%s]: Hai buttato i due dadi, ed e' uscito %d", game_name(), punteggio[0]);

        // se il punteggio è inferiore al precedente, il giocatore perde
        if(punteggio[0] < precedente[0]) {
            printf("\n[%s]: Peccato, hai fatto meno dell'ultimo tiro!", game_name());
            return 1;
        }



        // turno 2
        // stessa identica cosa del primo turno
        printf("\n[%s]: Tira i dadi, %s (invio)", game_name(), print_player(coppia[0]));
        getchar();

        punteggio[1] = rand_int(1, 6);
        punteggio[1] += rand_int(1, 6);
        printf("\n[%s]: Hai buttato i due dadi, ed e' uscito %d", game_name(), punteggio[1]);

        if(punteggio[1] < precedente[1]) {
            printf("\n[%s]: Peccato, hai fatto meno dell'ultimo tiro!", game_name());
            return 0;
        }


        // il punteggio precedente viene poi aggiornato di volta in volta
        precedente[0] = punteggio[0];
        precedente[1] = punteggio[1];

        printf("\n\n[%s]: Nessuno e' stato eliminato! Andiamo al prossimo turno!", game_name());
    }
}