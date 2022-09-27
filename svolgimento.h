//
// Created by Dando on 9/27/2022.
//

#ifndef DAVIDE_FLORE_66174_SVOLGIMENTO_H
#define DAVIDE_FLORE_66174_SVOLGIMENTO_H

#endif //DAVIDE_FLORE_66174_SVOLGIMENTO_H


# include "scrematura.h"





void svolgimento(Elenco *totale, int dim, Elenco *risultato, char *nome, int *numero_profili, ProfiloGiocatore *profili, int *numero_giocatori, int *numero_giocatori_veri) {

    int gioco, winner, segnaposto, membri, scelta, i;
    bool pla, game;

    Elenco *rimpiazzo = NULL;
    int dim_rimpiazzo = dim;

    Elenco gruppetto[4];

    char nome_file[32];






    // alloca l'array di rimpiazzo
    rimpiazzo = (Elenco *) malloc(sizeof(Elenco) * dim_rimpiazzo);
    if(rimpiazzo == NULL) {
        printf("\nERRORE! Allocazione fallita!\n");
        exit(-1);
    }
    // riempie l'array di rimpiazzo
    for(i = 0; i < dim; i++) {
        rimpiazzo[i] = totale[i];
    }

    // ciclo che si ripete fino a lasciare solo due giocatori rimasti
    while(dim_rimpiazzo > 2) {
        pla = false;

        // sceglie un gioco a caso
        if(dim_rimpiazzo >= 5) {
            gioco = rand_int(0, NUMERO_GIOCHI - 1);
        } else {
            gioco = rand_int(0, GIOCHI_SEMPLICI - 1);
        }

        // ricava il numero di giocatori per quel gioco
        if(gioco >= GIOCHI_SEMPLICI) {
            membri = 4;
        } else {
            membri = 2;
        }

        // riempie la squadra
        for(i = 0; i < membri; i++) {
            segnaposto = rand_int(0, 1);
            gruppetto[i] = rimpiazzo[segnaposto];

            if(is_player(gruppetto[i])) {
                gruppetto[i].p->giochi_giocati++;
                pla = true;
            }

            rimpiazzo[segnaposto] = rimpiazzo[dim_rimpiazzo - 1];
            dim_rimpiazzo--;
        }

        // gioca la partita e ottiene il vincitore
        if(pla) {
            switch (gioco) {
                case 0:
                    winner = murra(gruppetto);
                    break;
                case 1:
                    winner = tris(gruppetto);
                    break;
                default:
                    break;
            }
        } else {
            winner = rand_int(0, membri - 1);
        }

        // Frontman dello Spr1d Game
        i = 0;
        do {
            if(frontman(gruppetto[i])) {
                winner = i;
            }

            i++;
        } while(i < membri || frontman(gruppetto[i - 1]));

        // uccide tutti i giocatori perdenti
        for(i = 0; i < membri; i++) {
            if(i == winner && is_player(gruppetto[i])) {
                gruppetto[i].p->giochi_vinti++;
            } else {
                totale[gruppetto[i].id].vivo = false;
            }
        }

        // SALVA LA PARTITA IN CORSO
        printf("\n[%s]: Vuoi salvare la partita?\n[%s]", game_name(), nome);
        scelta = si_no(": ");

        if((bool)scelta) {
            printf("\n[%s]: Che nome vuoi dare al file? [ATTENTO, SE INSERISCI IL NOME DI UN FILE ESISTENTE, QUESTO VERRA' SOVRASCRITTO!]", game_name());
            printf("\n[%s]: ", nome);
            scanf(" %s", nome_file);

            game = true;
            save(numero_profili, profili, &game, nome_file, numero_giocatori, numero_giocatori_veri, totale);
        }
    }

    // recupera la coppia rimasta e mettila nel finale
    i = 0, segnaposto = 0;
    while(segnaposto < 2) {
        if(totale[i].vivo) {
            risultato[segnaposto] = totale[i];
            segnaposto++;
        }

        i++;
    }

    free(rimpiazzo);
}