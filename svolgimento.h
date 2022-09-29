//
// Created by Dando on 9/27/2022.
//

#ifndef DAVIDE_FLORE_66174_SVOLGIMENTO_H
#define DAVIDE_FLORE_66174_SVOLGIMENTO_H

#endif //DAVIDE_FLORE_66174_SVOLGIMENTO_H


#define NUMERO_GIOCHI 4


#include "scrematura.h"





// funzione che prende un Elenco, la su adimensione e una coppia di Elenco
// riempie la coppia in input con i finalisti per la fase finale
void svolgimento(Elenco *totale, int dim, Elenco *risultato) {

    int gioco, winner, segnaposto, membri, scelta, i;
    bool pla, front, is_game;
    int f_man = 0;

    Elenco *rimpiazzo = NULL;
    int dim_rimpiazzo = dim;

    Elenco gruppetto[2];
    int numero_gruppetti = dim;

    char nome_file[32];




    // alloca l'array di rimpiazzo usata per riempire i gruppetti
    rimpiazzo = (Elenco *) malloc(sizeof(Elenco) * dim_rimpiazzo);
    if(rimpiazzo == NULL) {
        printf("\nERRORE! Allocazione fallita!\n");
        exit(-1);
    }
    // riempie l'array di rimpiazzo
    for(i = 0; i < dim; i++) {
        rimpiazzo[i] = totale[i];
    }



    // riduce la lista a 2 giocatori
    while(numero_gruppetti > 2) {
        // di volta in volta, il nuemro di gruppetti si dimezza
        // come quello dei giocatori rimanenti dopo i giochi
        numero_gruppetti = dim_rimpiazzo / 2;

        // iterazione che riempie tutti i gruppetti
        for(i = 0; i < numero_gruppetti; i++) {
            pla = false;
            front = false;

            // viene prelevato un elemento sasuale dalla lista di rimpiazzo
            // questo metodo evita ripetizioni
            // usa la funzione tand_int() per evitare warnings da clion
            // rand_int() -> main.h
            segnaposto = rand_int(0, dim_rimpiazzo - 1);
            gruppetto[i] = rimpiazzo[segnaposto];
            rimpiazzo[segnaposto] = rimpiazzo[dim_rimpiazzo - 1];
            dim_rimpiazzo--;

            // se sono utenti, aggiorna le statistiche
            if(is_player(gruppetto[i])) {
                gruppetto[i].p->giochi_giocati++;
                pla = true;

                // e se sono Riccardo Scateni, si segna la posizione del frontman
                if(frontman(gruppetto[i])) {
                    front = true;
                    f_man = i;
                }
            }

            // sceglie il gioco a caso con rand_int() e la costante del numero dei giochi
            gioco = rand_int(0, NUMERO_GIOCHI - 1);

            // se il gruppo contiene un giocatore utente, recupera il gioco scelto a caso e fa una partita
            // altrimenti sceglie il vincitore a caso e risparmia tempo
            if(pla) {
                switch (gioco) {
                    case 0:
                        printf("\n[%s]: Si gioca a Murra! (invio)", game_name());
                        getchar();
                        winner = murra(gruppetto);
                        break;
                    case 1:
                        printf("\n[%s]: Si gioca a Morra Cinese! (invio)", game_name());
                        getchar();
                        winner = morra_cinese(gruppetto);
                        break;
                    case 2:
                        printf("\n[%s]: Si gioca a Dadi! (invio)", game_name());
                        getchar();
                        winner = dadi(gruppetto);
                        break;
                    case 3:
                        printf("\n[%s]: Si gioca a Pari o Dispari! (invio)", game_name());
                        getchar();
                        winner = pari_o_dispari(gruppetto);
                        break;
                    default:
                        printf("\nERRORE! Questo gioco non esiste!\n");
                        exit(-1);
                }
            } else {
                winner = rand_int(0, 1);
            }

            // frontman dello Sprid Game
            if(front) {
                winner = f_man;
            }

            // stampa il messaggio di vittoria
            printf("\n[%s]: VINCE %s!! (invio)", game_name(), print_player(gruppetto[winner]));
            getchar();



            // uccide i perdenti e aggiorna le vittorie
            // ho usato la proprietà dei booleani di essere interi per accedere a entrambi gli elementi del gruppo
            if(is_player(gruppetto[winner])) {
                gruppetto[winner].p->giochi_vinti++;
            }
            if(is_player(gruppetto[(int)!(bool)winner])) {
                giocatori[gruppetto[(int)!(bool)winner].id].vivo = false;
            }




            // SALVA LA PARTITA IN CORSO
            // proprio come in main.c, ma questa vola chiede all'utente se vuole continuare a giocare o uscire
            if(pla) {
                printf("\n[%s]: Vuoi salvare la partita? (si / no)\n[%s]", game_name(), nome_utente);
                scelta = (bool)si_no(": ");

                if(scelta) {
                    printf("\n[%s]: Come vuoi chiamare il file di salvataggio? (ATTENZIONE, SE SCEGLI IL NOME DI UN FILE ESISTENTE, QUESTO VERRA' SOVRASCRITTO!)", game_name());
                    scanf(" %s", nome_file);

                    is_game = false;
                    save(&is_game, nome_file);
                    add_file(nome_file);

                    printf("\n[%s]: Vuoi continuare a giocare? (si / no)\n[%s]", game_name(), nome_utente);
                    scelta = (bool)si_no(": ");

                    if(!scelta) {
                        printf("[%s]: D'accordo, alla prossima!", game_name());
                        exit(0);
                    }

                } else {
                    printf("\n[%s]: Bene, allora continuiamo (invio)\n", game_name());
                    getchar();
                }
            }
        }
    }


    // recupera la coppia finale e la salva nella coppia per la fase finale
    i = 0, segnaposto = 0;
    while(segnaposto < 2) {
        if(totale[i].vivo) {
            risultato[segnaposto] = totale[i];
            segnaposto++;
        }

        i++;
    }

    // infine libera l'array di rimpiazzo
    free(rimpiazzo);
}