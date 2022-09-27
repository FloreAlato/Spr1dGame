//
// Created by Dando on 9/27/2022.
//

#ifndef DAVIDE_FLORE_66174_GAMES_H
#define DAVIDE_FLORE_66174_GAMES_H

#endif //DAVIDE_FLORE_66174_GAMES_H


#define NUMERO_GIOCHI 2
#define GIOCHI_SEMPLICI 2



#include "indovina_il_numero.h"





int gioco_a_caso(int id, Elenco *giocatori, int dim) {

    int risultato;

    switch(id) {
        case 0:
            risultato = murra(giocatori);
            break;
        case 1:
            risultato = tris(giocatori);
            break;
        default:
            risultato = 0;
            break;
    }

    return risultato;
}