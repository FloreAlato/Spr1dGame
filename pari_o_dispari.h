//
// Created by Dando on 9/28/2022.
//

#ifndef DAVIDE_FLORE_66174_PARI_O_DISPARI_H
#define DAVIDE_FLORE_66174_PARI_O_DISPARI_H

#endif //DAVIDE_FLORE_66174_PARI_O_DISPARI_H



#include "dadi.h"




// gioco pari o dispari
// prende una coppia di Elenco e restituisce un intero
int pari_o_dispari(Elenco *coppia) {

    // i è un booleano per rendere il codice più malleabile
    char opzioni[2][10] = {"pari", "dispari"};
    int numeri[2];
    bool i = false, primo = false;

    printf("\n\n\n[%s]: Stai giocando a Pari o Dispari!!!\n\n", game_name());

    // se il primo giocatore non è utente, comincia il secondo
    if(!is_player(coppia[(int)i])) {
        i = true;
    }

    // chiede al giocatore che comincia di decidere se essere pari o dispari e salva la risposta nel booleano primo usando choice_string()
    // choice_string() -> main.h
    printf("\n[%s]: Vuoi essere pari o dispari? (pari / dispari)\n[%s]", game_name(), print_player(coppia[(int)i]));
    primo = (bool)choice_string(": ", 2, opzioni);
    getchar();

    // avvisa il'utente che l'altro giocatore userà il segno opposto
    printf("\n[%s]: Bene, allora %s sara' %s! (invio)", game_name(), print_player(coppia[(int)!i]), opzioni[(int)!primo]);
    getchar();

    // turno 1
    // il primo giocatore è per forza utente, quindi il numero viene raccolto con get_int()
    // get_int() -> main.h
    printf("\n\n\n[%s]: Adesso butta un numero da 0 a 5\n[%s]", game_name(), print_player(coppia[(int)i]));
    numeri[(int)i] = get_int(": ", 0, 5);
    getchar();


    // turno 2
    // il secondo giocatore può non essere utente, quindi la scelta si divide fra get_int() e rand_int()
    // rand_int() -> main.h
    printf("\n[%s]: Adesso butta un numero da 0 a 5\n[%s]", game_name(), print_player(coppia[(int)!i]));
    if(is_player(coppia[(int)!i])) {
        numeri[(int)!i] = get_int(": ", 0, 5);
    } else {
        numeri[(int)!i] = rand_int(0, 5);
        printf(": %d", numeri[(int)!i]);
        getchar();
    }


    // se la somma è pari e il primo giocatore ha scelto pari vince, altrimenti perde
    // se la somma è dispari e il primo giocatore ha scelto dispari vince, altrimenti perde
    if((numeri[0] - numeri[1]) % 2 == 0) {
        if(primo) {
            return (int)!i;
        } else {
            return (int)i;
        }
    } else {
        if(primo) {
            return (int)i;
        } else {
            return (int)!i;
        }
    }
}