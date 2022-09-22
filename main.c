#include "murra.h"



void scrematura(Elenco *, int);
void svolgimento(Elenco *, int);
void finale(Elenco *);




char **trova_nomi(FILE *, int);




int main() {

    int scelta, i;
    int numero_utenti;
    bool risposta;
    char nome_utente[64] = "Tu\0";
    char **nomi = NULL;
    FILE *file = NULL;





    // LOGIN / CREAZIONE PROFILO UTENTE

    printf("[%s]: Hai mai usato questo programma? (si / no)", game_name());
    printf("\n[%s]", nome_utente);
    risposta = si_no(": ");
    getchar();

    // apre il file con i profili utente e recuepra i nomi
    file = fopen_secure(make_path("users", ".bin"), "rb");
    fread(&numero_utenti, sizeof(int), 1, file);
    nomi = trova_nomi(file, numero_utenti);
    fclose(file);

    if(risposta) {
        // propone la scelta all'utente
        printf("\n[%s]: Quale di questi profili vuoi usare?\n", game_name());
        for(i = 0; i < numero_utenti; i++) {
            printf("[%d] -> %s", i, nomi[i]);
        }

        // salva il nome scelto come nome utente per la partita
        printf("\n[%s]", nome_utente);
        scelta = get_int(": ", 0, numero_utenti - 1);
        strcpy(nome_utente, nomi[scelta]);

    } else {
        // prende il nome dall'utente
        printf("\n[%s]: Bene allora, come vorresti chiamarti?\n[%s]: ", game_name(), nome_utente);
        scanf(" %s", nome_utente);
        getchar();

        numero_utenti++;

        // salva il nuovo nome nel file dei nomi
        file = fopen_secure(make_path("users", ".bin"), "wb");
        fwrite(&numero_utenti, sizeof(int), 1, file);

        for(i = 0; i < numero_utenti; i++) {
            fwrite(nomi[i], sizeof(char), 64, file);
        }
        fwrite(&nome_utente, sizeof(char), 64, file);

        fclose(file);
    }

    free(nomi);





    // SETUP SCHERMO


    printf("\n\n[%s]: Allora e' il caso di fare un po' di setup", game_name());
    printf("\n[%s]: Regola le dimensioni del terminale finche' non vedi il numero 25 (invio)", game_name());
    getchar();

    for(i = 1; i < PAGE_SIZE + 5; i++) {
        printf("%d\n", i);
    }
    printf("\n[%s]: Ora che hai regolato lo schermo, premi invio per cominciare (invio)", game_name());
    getchar();




    return 0;






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




char **trova_nomi(FILE *file, int numero_utenti) {

    int i;
    char **nomi = NULL;

    // cerca i nomi nel file

    nomi = (char **) malloc(sizeof(char *) * numero_utenti);
    if(nomi == NULL) {
        printf("\n\nERRORE! Allocazione fallita!\n\n");
        exit(-1);
    }

    for(i = 0; i < numero_utenti; i++) {
        nomi[i] = (char *) malloc(sizeof(char) * 64);
        if(nomi[i] == NULL) {
            printf("\n\nERRORE! Allocazione fallita!\n\n");
            exit(-1);
        }

        fread(nomi[i], sizeof(char), 64, file);
    }

    return nomi;
}

