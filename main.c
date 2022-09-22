#include "murra.h"



void scrematura(Elenco *, int);
void svolgimento(Elenco *, int);
void finale(Elenco *);




int main() {

    int i;


    srand(time(NULL));


    ProfiloGiocatore giovanni = {
            13,
            "Giovanni Maranza",
            0,
            0,
            0,
            0,
            0
    };


    Elenco fine[2] = {
            {
                0,
                true,
                &giovanni
            },
            {
                13,
                true,
                NULL
            }
    };


    // calibrazione


    // scrematura




    // svolgimento




    // finale
    getchar();
    int d = murra(fine);
    getchar();



    return 0;
}



