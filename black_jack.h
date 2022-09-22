//
// Created by dando on 17/08/2022.
//

#ifndef DAVIDE_FLORE_66174_BLACK_JACK_H
#define DAVIDE_FLORE_66174_BLACK_JACK_H

#endif //DAVIDE_FLORE_66174_BLACK_JACK_H

#include "main.h"



typedef enum {cuori, quadri, fiori, picche}semi;

typedef struct {
    semi seme;
    int valore;
}carta;



char card_img[5][11] = {
        " _______ ",
        "|      %s|",
        "|   %s  |",
        "|%s      |",
        " ------- "
};


int step = 8;



int black_jack(Elenco *);
void layout_black(int, carta **, int[2], Elenco *, int[2]);
void stampa_carta(carta *, int, int);
void recursione(carta *, int, int);
void stampa_vuota();
void segnapunti(carta *, int);





void layout_black(int page_size, carta **mazzi, int dim[2], Elenco *giocatori, int punteggio[2]) {

    int i, j;

    // 3 righe occupate
    printf("--------[STAI GIOCANDO A BLACKJACK]--------\n\n");


    // stampa carte avversario
    for(j = 0; j < 2; j++) {
        printf("Carte di %s (%d pt)\n", print_player(giocatori[j]), punteggio[j]);   // cambiare con i nomi dei giocatori

        if(mazzi[j] == NULL || dim[j] == 0) {
            stampa_vuota();

            for(i = 0; i < 5; i++) {
                printf("\n");
            }
        } else {
            recursione(&mazzi[j][0], 0, dim[j]);

            if(dim[j] <= step) {
                for(i = 0; i < 5; i++) {
                    printf("\n");
                }
            }
        }
    }


}




int black_jack(Elenco *finalisti) {


    bool pareggio = false;
    bool continua[2] = {true, true};
    int scelta, i, j, c = 0;
    int dim[2] = {2, 2};
    int punti[2] = {0, 0};

    int deck_size = 52, segnaposto;
    int end = 3;


    // genera il mazzo
    carta *mazzo = NULL;
    mazzo = (carta *) malloc(sizeof(carta) * deck_size);
    if(mazzo == NULL) {
        printf("ERRORE! Allocazione fallita!");
        exit(-1);
    }

    // riempi il mazzo
    for(i = 0; i < 4; i++) {
        for(j = 1; j <= 13; j++) {
            mazzo[c].seme = (semi)i;
            mazzo[c].valore = j;
            c++;
        }
    }


    carta **mazzi = NULL;
    mazzi = (carta **) calloc(2, sizeof(carta *));
    if(mazzi == NULL) {
        printf("ERRORE! Allocazione fallita!");
        exit(-1);
    }

    // partono con dimenzione 2
    mazzi[0] = (carta *) malloc(sizeof(carta) * dim[0]);
    mazzi[1] = (carta *) malloc(sizeof(carta) * dim[1]);
    if(mazzi[0] == NULL || mazzi[1] == NULL) {
        printf("ERRORE! Allocazione fallita!");
        exit(-1);
    }


    // rifare da capo (idiota)

    // riempi a caso le prime due carte
    for(i = 0; i < 2; i++) {
        for(j = 0; j < 2; j++) {
            segnaposto = rand_int(0, deck_size - 1);
            mazzi[i][j] = mazzo[segnaposto];
            mazzo[segnaposto] = mazzo[deck_size - 1];
            deck_size--;

            if(mazzi[i][j].valore == 1) {
                punti[i] += 11;
            } else if(mazzi[i][j].valore > 10) {
                punti[i] += 10;
            } else {
                punti[i] += mazzi[i][j].valore;
            }
        }
    }

    // COMINCIA LA PARTITA

    // mostra il tavolo
    while(continua[0] == true || continua[1] == true) {
        for(i = 0; i < 2; i++) {

            layout_black(25, mazzi, dim, finalisti, punti);


            if(continua[i]) {
                if(is_player(finalisti[i])) {

                    // turno giocatore
                    printf("Vuoi chiedere un'altra carta? (si / no)\n[%s]: ", print_player(finalisti[i]));
                    scelta = si_no("");
                    getchar();

                } else {

                    // turno non giocatore
                    // rivedere
                    scelta = rand_int(0, 1);

                    if(scelta) {
                        printf("\n[%s]: Dammene un'altra!", print_player(finalisti[i]));
                    } else {
                        printf("\n[%s]: Per me e' tutto!", print_player(finalisti[i]));
                    }

                    getchar();
                }

                // aggiorna in base alla scelta
                if(scelta) {
                    dim[i] += 1;
                    mazzi[i] = (carta *) realloc(mazzi[i], sizeof(carta) * dim[i]);

                    segnaposto = rand_int(0, deck_size - 1);
                    mazzi[i][dim[i] - 1] = mazzo[segnaposto];
                    mazzo[segnaposto] = mazzo[deck_size - 1];
                    deck_size--;

                    // aggiorna il punteggio
                    if(mazzi[i][dim[i] - 1].valore == 1) {

                        // vedere se l'utente vuole
                        layout_black(25, mazzi, dim, finalisti, punti);
                        printf("\nChe valore vuoi che abbia questo asso?\n[%s]: ", print_player(finalisti[i]));

                        punti[i] += 11;
                    } else if(mazzi[i][dim[i] - 1].valore > 10) {
                        punti[i] += 10;
                    } else {
                        punti[i] += mazzi[i][dim[i] - 1].valore;
                    }

                } else {
                    continua[i] = false;
                }

                // controlla che il punteggio non ecceda il massimo
                if(punti[i] > 21) {
                    end = not(i);
                    continua[i] = false;
                    continua[not(i)] = false;
                }
            }
        }
    }

    // punti





    free(mazzo);
    free(mazzi[0]);
    free(mazzi[1]);
    free(mazzi);

    return 1;

}






// riscrivere meglio e procedurale

void stampa_carta(carta *card, int start, int end) {


    int i, j;
    char scrivi[4] = "13\0";



    for(j = 0; j < 5; j++) {
        for(i = start; i < end; i++) {

            if(j == 2) {
                // valore
                if(card[i].valore > 1 && card[i].valore < 11) {
                    if(card[i].valore == 10) {
                        strcpy(scrivi, "10\0");
                    } else {
                        scrivi[0] = (char)(card[i].valore + 48);
                        scrivi[1] = ' ';
                        scrivi[2] = '\0';
                    }
                } else {
                    switch (card[i].valore) {
                        case 1:
                            strcpy(scrivi, "A \0");
                            break;
                        case 11:
                            strcpy(scrivi, "J \0");
                            break;
                        case 12:
                            strcpy(scrivi, "Q \0");
                            break;
                        case 13:
                            strcpy(scrivi, "K \0");
                            break;
                    }
                }
            } else {

                switch (card[i].seme) {
                    case cuori:
                        strcpy(scrivi, "C\0");
                        break;
                    case quadri:
                        strcpy(scrivi, "Q\0");
                        break;
                    case fiori:
                        strcpy(scrivi, "F\0");
                        break;
                    case picche:
                        strcpy(scrivi, "P\0");
                        break;
                }
            }

            printf(card_img[j], scrivi);
            printf("   ");
        }
        printf("\n");
    }
}



void recursione(carta *card, int start, int num) {

    if(num <= start + step) {

        // primi num
        stampa_carta(&card[0], start, num);

    } else {

        // recursione
        stampa_carta(&card[0], start, start + step);

        recursione(&card[0], start + step, num);
    }
}



void stampa_vuota() {

    printf(" _______ \n"
           "|       |\n"
           "|   ?   |\n"
           "|       |\n"
           " ------- ");
}




void segnapunti(carta *mazzo, int pos) {


}



