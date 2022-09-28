//
// Created by dando on 09/09/2022.
//

#ifndef DAVIDE_FLORE_66174_TRIS_H
#define DAVIDE_FLORE_66174_TRIS_H

#endif //DAVIDE_FLORE_66174_TRIS_H


#include "black_jack.h"


//typedef enum {centro, vicino, angolo, lontano, opposto}Strategy;




int tris(Elenco *);
void stampa_tabella();
void layout_tris(Elenco *, int, bool);
void stampa_turno(Elenco *, int, int);
bool turno_tris(int *, Elenco);
void tris_bot(int *, int);

bool isCenter(const int *);
bool isAngle(const int *);
bool isEdge(const int *);



char tavola[3][3] = {
        '-', '-', '-',
        '-', '-', '-',
        '-', '-', '-'
};

int mosse[9][2] = {
        3, 3,
        3, 3,
        3, 3,
        3, 3,
        3, 3,
        3, 3,
        3, 3,
        3, 3,
        3, 3
};

int angles[4][2] = {
        0, 0,
        0, 2,
        2, 0,
        2, 2
};









int tris(Elenco *coppia) {

    int turno = 0;

    bool i = false;
    bool won = false;
    bool giusto = false;
    char segni[2] = {'X', 'O'};
    char num1[2], num2[2];
    int coordinate[2];

    num1[1] = num2[1] = '\0';




    // turno
    do {
        do {
            if(is_player(coppia[(int)i])) {
                layout_tris(coppia, (int)i, false);
                giusto = turno_tris(&coordinate[0], coppia[(int)i]);

                if(giusto == true) {
                    tavola[coordinate[0]][coordinate[1]] = segni[(int)i];
                }

            } else {
                layout_tris(coppia, (int)i, false);
                tris_bot(&coordinate[0], i);
                printf("\nhehe");

                tavola[coordinate[0]][coordinate[1]] = segni[(int)i];

                getchar();
            }
        } while(giusto == false);

        // aggiorna la lista delle mosse
        mosse[turno][0] = coordinate[0];
        mosse[turno][1] = coordinate[1];

        // controllare punteggio e vittoria
        /*
         * controlla verticale e orizzontale
         * controlla le oblique
         * se hai vinto, interrompi
         */



        i = !i;
        turno++;

    } while(won == false);

    // mostra la schermata di vittoria

    // ritorna il vincitore
    return 0;
}






void stampa_tabella() {

    int i, c = 0;

    char table_image[2][15] = {
            " %c | %c | %c \0",
            "---|---|---\0"
    };

    for(i = 0; i < 5; i++) {
        if(i % 2 == 0) {
            printf(table_image[0], tavola[c][0], tavola[c][1], tavola[c][2]);
            c++;
        } else {
            printf(table_image[1], "");
        }
        printf("\n");
    }
}





void layout_tris(Elenco *players, int turno, bool vittoria) {

    int i;

    // 3 righe occupate
    printf("--------[STAI GIOCANDO A BLACKJACK]--------\n\n");

    // stampa tabella (5 righe occupate)
    stampa_tabella();

    // 2 righe occupate
    printf("\n\n");

    // 4 righe occupate
    stampa_turno(players, 2, turno);

    // 14 in totale


    if(vittoria) {
        printf("\n\n\n\n\n[%s]: VITTORIAAA!!!\n\n\n\n\n", game_name());
    } else {
        for(i = 14; i <= PAGE_SIZE; i++) {
            printf("\n");
        }
    }
}




void stampa_turno(Elenco *players, int num, int turno) {

    int i, j;

    printf("TOCCA A:\n\n");
    for(i = 0; i < num; i++) {

        if(i == turno) {
            printf("|");
        } else {
            printf(" ");
        }

        printf("%s ", print_player(players[i]));
    }
    printf("\n");

    for(i = 0; i < num; i++) {
        if(i == turno) {
            printf("|");
            for(j = 0; j < strlen(print_player(players[i])); j++) {
                printf("_");
            }
        } else {
            for(j = 0; j <= strlen(print_player(players[i])); j++) {
                printf(" ");
            }
            printf(" ");
        }
    }

}







bool turno_tris(int *coordinate, Elenco giocatore) {

    char risposta[4] = "A,B\0";
    char num1[2], num2[2];

    num1[1] = num2[1] = '\0';


    printf("[%s]: Dove vuoi mettere il tuo segno? (1,2)\n[%s]: ", game_name(), print_player(giocatore));
    scanf(" %s", risposta);
    getchar();

    // controlla risposta
    num1[0] = risposta[0];
    num2[0] = risposta[2];

    // controlla che il formato sia giusto
    if(is_numeric(num1) && is_numeric(num2) && risposta[1] == ',') {

        // controlla che la casella esista
        coordinate[0] = string_to_int(num1);
        coordinate[1] = string_to_int(num2);

        if(coordinate[0] >= 0 && coordinate[0] < 3 && coordinate[1] >= 0 && coordinate[1] < 3) {

            // controlla che la casella sia libera
            if(tavola[coordinate[0]][coordinate[1]] == '-') {

                return true;

            } else {
                printf("\nQUESTA CASELLA E' GIA' OCCUPATA!!!!!");
                getchar();
                return false;
            }

        } else {
            printf("\nQUESTA CASELLA NON ESISTE!!!!!");
            getchar();
            return false;
        }

    } else {
        printf("\nFORMATO SBAGLIATO!!!!!");
        getchar();
        return false;
    }
}






void tris_bot(int *coordinate, int turno) {

    int segnaposto;

    if(turno == 0) {
        // se inizia il bot mette in un angolo a caso
        segnaposto = rand_int(0, 3);
        coordinate[0] = angles[segnaposto][0];
        coordinate[1] = angles[segnaposto][1];

    } else if(turno == 1) {
        // se tu metti in un angolo, mette al centro
        if(isAngle(mosse[0])) {
            coordinate[0] = coordinate[1] = 1;
        } else {
            // altrimenti mette in un angolo a caso
            // che sia diverso da dove hai messo tu
            do {
                segnaposto = rand_int(0, 3);
            } while(angles[segnaposto][0] == mosse[0][0] && angles[segnaposto][1] == mosse[0][1]);
            coordinate[0] = angles[segnaposto][0];
            coordinate[1] = angles[segnaposto][1];
        }
    } else if(turno == 2) {

    }
}



bool check_tris(const int *coord, char sign) {

    if(tavola[coord[0]][coord[1]] == sign) {
        return true;
    } else {
        return false;
    }
}


bool isCenter(const int *coordinate) {
    if(coordinate[0] == coordinate[1] == 1) {
        return true;
    } else {
        return false;
    }
}

bool isAngle(const int *coordinate) {
    if(coordinate[0] == coordinate[1] && (coordinate[0] == 0 || coordinate[1] == 2)) {
        return true;
    } else {
        return false;
    }
}

bool isEdge(const int *coordinate) {
    if(!isAngle(coordinate) && !isCenter(coordinate)) {
        return true;
    } else {
        return false;
    }
}

