//
// Created by dando on 17/08/2022.
//

#ifndef DAVIDE_FLORE_66174_BLACK_JACK_H
#define DAVIDE_FLORE_66174_BLACK_JACK_H

#endif //DAVIDE_FLORE_66174_BLACK_JACK_H

#include "file.h"


// enumeratore dei possibili valori dei semi
typedef enum {cuori, quadri, fiori, picche}semi;

// struttura carta che contiene seme e valore di tutte le carte
typedef struct {
    semi seme;
    int valore;
}carta;

// matrice immagine della carta, si usa per stampare le carte
char card_img[5][11] = {
        " _______ ",
        "|      %s|",
        "|   %s  |",
        "|%s      |",
        " ------- "
};

// intero che decide quante carte si possono stampare prima di andare a capo
int step = 8;



int black_jack(Elenco *);
void layout_black(carta **, int[2], Elenco *, int[2], bool);
void stampa_carta(carta *, int, int);
void recursione(carta *, int, int);
void stampa_vuota();




// layout del gioco blackjack
// prende due mazzi di carte e le loro dimensioni, un arry di giocatori, i loro punteggi e un booleano per la vittoria
void layout_black(carta **mazzi, int dim[2], Elenco *gamers, int punteggio[2], bool vittoria) {

    int i, j;

    // 3 righe occupate
    printf("--------[STAI GIOCANDO A BLACKJACK]--------\n\n");


    // stampa i mazzi dei due giocatori in modo ordinato
    // stampa prima il nome del giocatore usando print_player() e poi le carte in ordine usando recursione()
    for(j = 0; j < 2; j++) {
        printf("Carte di %s (%d pt)\n", print_player(gamers[j]), punteggio[j]);

        if(mazzi[j] == NULL || dim[j] == 0) {
            stampa_vuota();
        } else {
            recursione(&mazzi[j][0], 0, dim[j]);
        }

        printf("\n");
    }

    // se la partita è vinta, stampa un messaggio di vittoria
    // altrimenti fa spazio per riempire la pagina
    if(vittoria) {
        // vinci
        printf("\n\n\n\n[%s]: VITTORIA!!!! FINE DELLA PARTITA!!!\n\n\n", game_name());
    } else {
        for(i = 16; i < PAGE_SIZE- 2; i++) {
            printf("\n");
        }
    }
}






// gioco blackjack
// prende una coppia di giocatori e restituisce l'indice del vincitore
int black_jack(Elenco *finalisti) {

    // variabili per le varie fasi del gioco
    bool pareggio = false;
    bool continua[2] = {true, true};
    int scelta, i, j, c = 0;
    int dim[2] = {2, 2};
    int punti[2] = {0, 0};

    int deck_size = 52, segnaposto;
    int end = 3;
    int risposta;
    bool ripeti = false;


    // genera dinamicamente l'arry di carte che conterrà il mazzo
    carta *mazzo = NULL;
    mazzo = (carta *) malloc(sizeof(carta) * deck_size);
    if(mazzo == NULL) {
        printf("ERRORE! Allocazione fallita!");
        exit(-1);
    }

    // riempie il mazzo con tutte le carte e i semi possibili andando per ordine
    // è il motivo per cui i semi sono organizzati in un enumeratore
    for(i = 0; i < 4; i++) {
        for(j = 1; j <= 13; j++) {
            mazzo[c].seme = (semi)i;
            mazzo[c].valore = j;
            c++;
        }
    }

    // alloca la matrice che conterrà i due mazzi
    carta **mazzi = NULL;
    mazzi = (carta **) calloc(2, sizeof(carta *));
    if(mazzi == NULL) {
        printf("ERRORE! Allocazione fallita!");
        exit(-1);
    }

    // alloca i due mazzi individualmente e li inizializza a due carte come da consegna
    mazzi[0] = (carta *) malloc(sizeof(carta) * dim[0]);
    mazzi[1] = (carta *) malloc(sizeof(carta) * dim[1]);
    if(mazzi[0] == NULL || mazzi[1] == NULL) {
        printf("ERRORE! Allocazione fallita!");
        exit(-1);
    }

    // riempie le prime e uniche due posizioni di ogni mazzo con carte a caso
    // il metodo usato è lo stesso di tutti gli altri riempimenti casuali in questo progetto
    // le carte scelte vengono sostituite man mano dalle ultime, e la lista provvisoria (in questo caso il mazzo) si riduce gradualmente
    // permette di riempire casualmente i mazzi in modo ordinato e aumenta la randomicità
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

    // la partita va avanti finchè entrambi i giocatori vogliono/possono continuare
    // questo stato è salvato in un array di due booleani
    while(continua[0] == true || continua[1] == true) {
        // itera fra i due giocatori
        for(i = 0; i < 2; i++) {
            // se il giocatore può continuare, stampa il layout e prosegui, altrimenti passa al turno successivo
            if(continua[i]) {

                layout_black(mazzi, dim, finalisti, punti, false);

                // se il giocatore di turno è controllato dall'utente, prende la scelta con si_no()
                if(is_player(finalisti[i])) {

                    printf("[%s]: Vuoi chiedere un'altra carta? (si / no)\n[%s]", game_name(), print_player(finalisti[i]));
                    scelta = si_no(": ");
                    getchar();

                } else {
                    // altrimenti la sceglie in base a quanto manca per arrivare a 21
                    // non è complesso, ma funziona bene
                    if(21 - punti[i] > 3) {
                        scelta = 1;
                        printf("[%s]: Vuoi chiedere un'altra carta?\n[%s]: Dammene un'altra!" , game_name(), print_player(finalisti[i]));
                    } else {
                        scelta = 0;
                        printf("[%s]: Vuoi chiedere un'altra carta?\n[%s]: Per me e' tutto!" , game_name(), print_player(finalisti[i]));
                        continua[i] = false;
                    }
                    // aspetta sempre l'input del giocatore per maggiore fluidità
                    getchar();
                }

                // se il giocatore vuole un'altra carta, aggiorna il mazzo corrispondente
                // fa ciò riallocando il mazzo corrispondente e mettendoci una carta nuova con il solito metodo
                if(scelta) {
                    dim[i] += 1;
                    mazzi[i] = (carta *) realloc(mazzi[i], sizeof(carta) * dim[i]);

                    segnaposto = rand_int(0, deck_size - 1);
                    mazzi[i][dim[i] - 1] = mazzo[segnaposto];
                    mazzo[segnaposto] = mazzo[deck_size - 1];
                    deck_size--;

                    // una volta inserita la nuova carta, aggiorna il punteggio di conseguenza
                    // se il giocatore ha ottenuto un asso, potrà decidere che valore dargli
                    if(mazzi[i][dim[i] - 1].valore == 1 && is_player(finalisti[i])) {

                        // chiede all'utente il valore da dare all'asso
                        layout_black(mazzi, dim, finalisti, punti, false);
                        printf("\n[%s]: Che valore vuoi che abbia questo asso? (1 / 11)\n[%s]", game_name(), print_player(finalisti[i]));

                        // poi itera per debuggare la risposta
                        // usare get_int() per questa parte da risultati un po' bizzarri in caso di errore
                        // ma non valeva la pena scrivere un'intera funzione solo per questo, e inoltre funziona bene
                        do {
                            risposta = get_int(": ", 1, 11);

                            if(risposta == 1) {
                                punti[i] += 1;
                            } else if(risposta == 11) {
                                punti[i] += 11;
                            } else {
                                printf("\n[%s]: Errore! puoi scegliere solo 1 o 11", game_name());
                            }
                        } while(risposta != 1 && risposta != 11);

                        // i non utenti non hanno il lusso di scegliere, i loro assi valgono sempre 11
                        // altrimenti aggiunge al punteggio il valore della carta o figura corrispondente
                    } else if(mazzi[i][dim[i] - 1].valore == 1) {
                        punti[i] += 11;
                    } else if(mazzi[i][dim[i] - 1].valore > 10) {
                        punti[i] += 10;
                    } else {
                        punti[i] += mazzi[i][dim[i] - 1].valore;
                    }

                    // se il giocatore / bot sceglie di non ricevere altre carte, perde diritto ai suoi turni successivi
                } else {
                    continua[i] = false;
                }

                // infine, se il punteggio del giocatore eccede 21, il gioco finisce e la variabile end riceve l'indice dell'avversario
                if(punti[i] > 21) {
                    if(i == 0) {
                        end = 1;
                    } else {
                        end = 0;
                    }
                    continua[0] = false;
                    continua[1] = false;
                }
            }
        }

    }

    // quando la partita è finita, il programma stampa il layout di vittoria e aspetta l'input dell'utente
    layout_black(mazzi, dim, finalisti, punti, true);
    printf("\n[%s]: %d si aggiudica la partita!", game_name(), end);
    getchar();

    // poi libera turra la memoria inutile
    free(mazzo);
    free(mazzi[0]);
    free(mazzi[1]);
    free(mazzi);

    // e ritorna l'indice del vincitore
    return 1;
}






// funzione che stampa una serie di carte da start a end
// prende in input un array di carte
void stampa_carta(carta *card, int start, int end) {


    int i, j;
    char scrivi[4] = "13\0";


    // dato che usa una matrice per stampare ogni carta, itera prima fra le prime righe di ogni carta, poi le seconde e così via
    for(j = 0; j < 5; j++) {
        for(i = start; i < end; i++) {

            // il valore richiede una procedura diversa rispetto ai semi
            if(j == 2) {
                // per allineare bene le immagini, stampa normalmente il 10
                // ma mette uno spazio alla fine se il numero ha una sola cifra
                // i numeri sono trasformati in stringhe sfruttando il loro ordine nel sistema ascii
                if(card[i].valore > 1 && card[i].valore < 11) {
                    if(card[i].valore == 10) {
                        strcpy(scrivi, "10\0");
                    } else {
                        scrivi[0] = (char)(card[i].valore + 48);
                        scrivi[1] = ' ';
                        scrivi[2] = '\0';
                    }
                } else {
                    // per stampare le lettere, invece, deve fare una switch e decidere in ogni caso la lettera giusta
                    // notare come è comunque presente lo spazio per via della cifra unica
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
                // i semi vengono stampati come le figure
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

            // qui è dove viene effettivamente stampata la carta
            // insieme allo spazio che la separa dalle altre
            printf(card_img[j], scrivi);
            printf("   ");
        }
        // poi si va a capo
        printf("\n");
    }
}


// funzione di stampa ricorsiva delle carte
// il mio orgoglio, tragicamente inutile
// stampa le carte per righe di massimo 5 carte, andando a capo di volta in volta
// sfortunatamente, non ho mai fatto una partita che richiedesse più di 5 carte
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


// questa funzione nasce da un'incorretta lettura della consegna
//serviva a tenere la tavola ordinata qualora non ci dovessero essere carte in campo
// ironicamente, ci sono sempre carte in campo
void stampa_vuota() {

    printf(" _______ \n"
           "|       |\n"
           "|   ?   |\n"
           "|       |\n"
           " ------- ");
}



