//
// Created by Dando on 9/29/2022.
//

#ifndef DAVIDE_FLORE_66174_MORRA_CINESE_H
#define DAVIDE_FLORE_66174_MORRA_CINESE_H

#endif //DAVIDE_FLORE_66174_MORRA_CINESE_H



#include "pari_o_dispari.h"


// struttura segno che contiene i segni in ordine
typedef enum {paper, scissors, rock}segno;

// struttura butta che conterrà i segni e le loro affinità con gli altri segni
typedef struct {
    segno s;
    segno batte;
    segno perde;
}butta;

// array con i segni e le loro affinità, per reference
butta sengi[3] = {
        {paper, rock, scissors},
        {scissors, paper, rock},
        {rock, scissors, paper}
};





// gioco carta forbici sasso
// prende una coppia di Elenco e restituisce un intero
int morra_cinese(Elenco *coppia) {

    // i è un booleano per rendere il codice più malleabile
    bool i;
    char scelte[3][10] = {"carta", "forbici", "sasso"};
    segno decisione[2];

    // se il primo giocatore è utente comincia lui, altrimenti comincia il secondo
    if(is_player(coppia[0])) {
        i = false;
    } else {
        i = true;
    }

    printf("\n\n\n[%s]: Stai giocando a Carta Forbice Sasso!!\n\n", game_name());

    while(true) {

        // turno 1
        // la decisione è un segno, e viene presa tramite choice_string() e trasformata in segno
        // choice_string -> main.h
        printf("\n[%s]: Butta un segno (carta, forbici, sasso)\n[%s]", game_name(), print_player(coppia[(int)i]));
        decisione[(int)i] = (segno)choice_string(": ", 3, scelte);
        getchar();

        // turno 2
        // qui bisogna differenziare, perchè non sappiamo se il secondo giocatore sia utente o meno
        // se non è utente, il segno viene scelto a caso
        if(is_player(coppia[(int)!i])) {
            printf("\n[%s]: Butta un segno (carta, forbici, sasso)\n[%s]", game_name(), print_player(coppia[(int)!i]));
            decisione[(int)!i] = (segno)choice_string(": ", 3, scelte);
            getchar();
        } else {
            decisione[(int)!i] = (segno)rand_int(0, 2);
            printf("\n[%s]: Butta un segno (carta, forbici, sasso)\n[%s]: %s", game_name(), print_player(coppia[(int)i]), scelte[(int)decisione[(int)!i]]);
            getchar();
        }

        // controlla vittoria
        // qui entra in gioco l'array segni
        // il programma controlla la posizione dei segni rispettiva alla scelta del primo giocatore
        // se vince contro la scelta del secondo, vince
        // se perde contro la scelta del secondo, perde
        // altrimenti pareggia e il gioco si ripete
        if(sengi[decisione[(int)i]].batte == decisione[(int)!i]) {
            printf("\n[%s]: Vince %s!\n", game_name(), print_player(coppia[(int)i]));
            return (int)i;
        } else if(sengi[decisione[(int)i]].perde == decisione[(int)!i]) {
            printf("\n[%s]: Vince %s!\n", game_name(), print_player(coppia[(int)!i]));
            return (int)!i;
        } else {
            printf("\n[%s]: Pareggio! (invio)", game_name());
            getchar();
            printf("\n\n\n");
        }
    }
}