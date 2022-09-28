//
// Created by Dando on 9/23/2022.
//

#ifndef DAVIDE_FLORE_66174_SCREMATURA_H
#define DAVIDE_FLORE_66174_SCREMATURA_H

#endif //DAVIDE_FLORE_66174_SCREMATURA_H


#include "indovina_il_numero.h"



Elenco *scrematura(Elenco *, int, int *);
void stampa_gruppetti(Elenco **, int, int, int);
void stampa_ricorsiva(Elenco **, int, int, int);











int step_stampa = 5;









Elenco *scrematura(Elenco *participants, int totale, int *target) {

    int i = 0, j, k, counter;
    int group_size, segnaposto, dim, winner;

    Elenco *nuovo = NULL;
    Elenco **groups = NULL;
    bool *pla = NULL;

    bool scelta, game;
    char filename[32];



    // ELENCO PROVVISORIO PER RIEMPIRE



    // nuovo elenco
    nuovo = (Elenco *) calloc(totale, sizeof(Elenco));
    if(nuovo == NULL) {
        printf("\n\nERRORE! Allocazione fallita!\n\n");
        exit(-1);
    }
    for(k = 0; k < totale; k++) {
        nuovo[k] = participants[k];
    }


    // ottiene il numero desiderato di giocatori
    while(potenza(2, i) < totale) {
        i++;
    }
    *target = potenza(2, i - 2);
    printf("\n\n\n[%s]: Troppi! Facciamo %d? (invio)", game_name(), *target);
    getchar();

    // dividi in gruppetti
    group_size = totale / *target;

    // alloca i gruppetti
    groups = (Elenco **) calloc(*target, sizeof(Elenco *));
    if(groups == NULL) {
        printf("\n\nERRORE! Allocazione fallita!");
        exit(-1);
    }
    for(i = 0; i < *target; i++) {
        groups[i] = (Elenco *) calloc(group_size + 1, sizeof(Elenco));
        if(groups[i] == NULL) {
            printf("\n\nERRORE! Allocazione fallita!");
            exit(-1);
        }
    }


    // riempie l'array pla
    pla = (bool *) calloc(*target, sizeof(bool));
    if(pla == NULL) {
        printf("\n\nERRORE! Allocazione fallita!\n\n");
        exit(-1);
    }
    for(i = 0; i < *target; i++) {
        pla[i] = false;
    }



    // RIEMPIE I GRUPPETTI IN MODO CASUALE




    // riempie i gruppetti randomizzando
    counter = totale - 1;
    for(i = 0; i <= group_size; i++) {
        for(j = 0; j < *target; j++, counter--) {
            if(counter >= 0) {
                segnaposto = rand_int(0, counter);
                groups[j][i] = nuovo[segnaposto];

                // salva i gruppi che contengono giocatori
                if(is_player(groups[j][i])) {
                    pla[j] = true;
                }

                nuovo[segnaposto] = nuovo[counter];
            } else {
                groups[j][i].id = -1;
            }
        }
    }



    // stampa i gruppetti in modo ordinato
    printf("\n\n\n");
    stampa_ricorsiva(groups, group_size, 0, *target);
    getchar();

    printf("\n\n");






    // RIVEDI TUTTA QUESTA PARTE




    // rialloca elenco
    nuovo = (Elenco *) realloc(nuovo, sizeof(Elenco) * *target);
    if(nuovo == NULL) {
        printf("\n\nERRORE! Rillocazione fallita!\n\n");
        exit(-1);
    }


    // SCORRI IL GRUPPO E GIOCA
    // l'ultimo elemento dei gruppi piccoli ha id -1
    for(i = 0; i < *target; i++) {

        if(groups[i][group_size].id == -1) {
            dim = group_size - 1;
        } else {
            dim = group_size;
        }


        // controlla che ci siano giocatori e agisci di conseguenza
        if(pla[i]) {
            // gioca
            printf("\n\n[%s]: Il %do gruppo contiene un giocatore", game_name(), i + 1);
            printf("\n[%s]: Giochiamo a Indovina il Numero!! (invio)", game_name());
            getchar();

            // GIOCA A INDOVINA IL NUMERO

            winner = indovina_il_numero(groups[i], dim + 1);

            // FRONTMAN DELLO SPR1D GAME
            for(j = 0; j < dim; j++) {
                if(frontman(groups[i][j])) {
                    winner = j;
                }
                if(is_player(groups[i][j])) {
                    groups[i][j].p->giochi_giocati++;
                }
            }

            // vincitore
            printf("\nVINCE %s", print_player(groups[i][winner]));

            // aggiorna le statistiche del giocatore
            if(is_player(nuovo[i])) {
                nuovo[i] = groups[i][winner];
                nuovo[i].p->giochi_vinti++;
            }

        } else if(!pla[i] || i == *target - 1) {
            // scegli il vincitore a caso
            winner = rand_int(0, dim);
            nuovo[i] = groups[i][winner];
            printf("\n[%s]: Il %do gruppo ha giocato e ha vinto %s", game_name(), i + 1, print_player(nuovo[i]));
        }

        // uccidi tutti i perdenti e aumenta le statistiche dei profili giocatore
        for(k = 0; k < dim; k++) {
            if(k != winner) {
                participants[groups[i][k].id].vivo = false;
            }
            if(is_player(participants[groups[i][k].id])) {
                participants[groups[i][k].id].p->giochi_giocati++;
            }
        }

        // SALVA IN UN FILE SENZA GIOCO
        // solo se la partita è stata giocata dall'utente
        if(pla[i]) {
            printf("\n[%s]: Vuoi salvare la partita? (si / no)\n[%s]", game_name(), nome_utente);
            scelta = (bool)si_no(": ");

            if(scelta) {
                printf("\n[%s]: Come vuoi chiamare il file di salvataggio? (ATTENZIONE, SE SCEGLI IL NOME DI UN FILE ESISTENTE, QUESTO VERRA' SOVRASCRITTO!)", game_name());
                scanf(" %s", filename);

                game = false;
                save(&game, filename);
                add_file(filename);

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


    // ora i gruppi non servono più
    free(groups);

    return nuovo;
}











void stampa_ricorsiva(Elenco **groups, int size, int start, int tot) {

    if(tot <= start + step_stampa) {
        stampa_gruppetti(groups, size, start, tot);
    } else {
        stampa_gruppetti(groups, size, start, start + step_stampa);

        stampa_ricorsiva(groups, size, start + step_stampa, tot);
    }
}






void stampa_gruppetti(Elenco **groups, int size, int start, int finish) {

    int j, k, t;

    printf("\n");

    for(j = start; j < finish; j++) {
        printf("%do gruppo:            ", j + 1);
        if(j > 99) {
            printf("  ");
        } else if(j > 9) {
            printf(" ");
        }
    }

    printf("\n");

    for(j = 0; j <= size; j++) {
        for(k = start; k < finish; k++) {

            if(is_player(groups[k][j])) {
                if(strlen(groups[k][j].p->nome) >= 21) {
                    for(int d = 0; d <= 21; d++) {
                        printf("%c", groups[k][j].p->nome[d]);
                    }
                    printf(" ");
                } else {
                    printf("%s", groups[k][j].p->nome);
                    for(t = 0; t < 22 - strlen(groups[k][j].p->nome); t++) {
                        printf(" ");
                    }
                }
            } else {
                printf("%s         ", print_player(groups[k][j]));
            }

        }
        printf("\n");
    }
}



