#include "murra.h"



void scrematura(Elenco *, int);
void svolgimento(Elenco *, int);
void finale(Elenco *);




int main() {

    // TESTING
    int i, j, k, l, counter;

    int numero_giocatori, numero_giocatori_veri;
    Elenco *giocatori = NULL;
    ProfiloGiocatore *giocatori_veri;
    FILE *file = NULL;

    bool nuovo, esistente, scelto, game = false;
    int scelta, prosegui;
    char nome_giocatore[32];
    char opzioni[2][10] = {"carica", "inserisci"};
    char scelte[4][10] = {"continua", "salva", "inizia", "esci"};
    char **files = NULL;
    int numero_files;
    int numero_profili;

    int id, segnaposto;
    Elenco *prov = NULL;

    Elenco **groups = NULL;
    Elenco *new = NULL;
    bool *pla = NULL;
    int target, group_size, size, winner;






    int numero_utenti;
    bool risposta;
    char nome_utente[32] = "Tu";
    char **nomi = NULL;


    /*int n = 1;
    file = fopen_secure(make_path("users", ".bin"), "wb");
    fwrite(&n, sizeof(int), 1, file);
    fwrite(nome_utente, sizeof(char), 32, file);
    fclose(file);*/


    //return 0;


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
        printf("\n[%s]: Quale di questi e' il tuo nome?\n", game_name());
        for(i = 0; i < numero_utenti; i++) {
            printf("[%d] -> %s\n", i, nomi[i]);
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

        for(i = 0; i < numero_utenti - 1; i++) {
            fwrite(nomi[i], sizeof(char), 64, file);
        }
        fwrite(&nome_utente, sizeof(char), 64, file);

        fclose(file);
    }

    free(nomi);




    // SETUP SCHERMO


    printf("\n\n[%s]: Perfetto, %s! E' il caso di fare un po' di setup", game_name(), nome_utente);
    printf("\n[%s]: Regola le dimensioni del terminale finche' non vedi il numero 25 (invio)", game_name());
    getchar();

    for(i = 1; i < PAGE_SIZE + 5; i++) {
        printf("%d\n", i);
    }
    printf("\n[%s]: Ora che hai regolato lo schermo, premi invio per cominciare (invio)", game_name());
    getchar();








    // AVVIO PROGRAMMA, SCELTA DELL'OPERAZIONE


    printf("\n\n\n[%s]: Cosa vuoi fare? (carica / inserisci)\n[%s]", game_name(), nome_utente);
    nuovo = (bool)choice_string(": ", 2, opzioni);

    if(nuovo) {
        // se vuole inserire, si parte da 1 profilo giocatore
        numero_profili = 1;

        giocatori_veri = (ProfiloGiocatore *) calloc(numero_profili, sizeof(ProfiloGiocatore));
        if(giocatori_veri == NULL) {
            printf("\n\nERRORE! Allocazione fallita!");
            exit(-1);
        }

        // inserimento nuovi profili
        do {

            // serve per evitare passaggi inutili
            if(numero_profili > 1) {
                giocatori_veri = (ProfiloGiocatore *) realloc(giocatori_veri, sizeof(ProfiloGiocatore) * numero_profili);
            }

            do {
                esistente = false;

                // inserimento del nome (accetta anche gli spazi)
                printf("\n[%s]: Nome giocatore\n[%s]: ", game_name(), nome_utente);
                scanf (" %[^\n]%*c", nome_giocatore);

                // confronta con le precedenti
                for(i = 0; i < numero_profili; i++) {
                    if(strcmp(giocatori_veri[i].nome, nome_giocatore) == 0) {
                        esistente = true;
                        printf("\n\n[%s]: Hai gia' inserito questo nome\n\n", game_name());
                        break;
                    }
                }

            } while(esistente == true);


            // azzera tutto
            strcpy(giocatori_veri[numero_profili - 1].nome, nome_giocatore);
            giocatori_veri[numero_profili - 1].index = 0;
            giocatori_veri[numero_profili - 1].spr1d_game_giocati = 0;
            giocatori_veri[numero_profili - 1].spr1d_game_vinti = 0;
            giocatori_veri[numero_profili - 1].finali_giocate = 0;
            giocatori_veri[numero_profili - 1].giochi_giocati = 0;
            giocatori_veri[numero_profili - 1].giochi_vinti = 0;

            // prosegue o ripete
            printf("\n[%s]: Scegli l'operazione: (continua / salva / inizia / esci)\n[%s]", game_name(), nome_utente);
            prosegui = choice_string(": ", 4, scelte);

            // si aumenta il numero dei profili
            numero_profili++;

        } while(prosegui == 0);

        numero_profili--;






        // decide cosa fare poi
        switch(prosegui) {
            case 1:
                printf("\n[%s]: Inserisci il nome del file nel quale vorresti salvare i profili", game_name());
                printf("\n[%s]: (ATTENZIONE! Se inserirai il nome di un file esistente, questo verrà sovrascritto!)", game_name());

                // riutilizza la variabile nome_giocatore
                printf("\n\n[%s]: ", nome_utente);
                scanf(" %s", nome_giocatore);

                // salva la partita in un file senza gioco
                save(&numero_profili, giocatori_veri, false, nome_giocatore);
                add_file(nome_giocatore);
                break;
            case 2:
                printf("\n\n\n[%s]: ALLORA COMINCIAMO!!!!! (invio)", game_name());
                getchar();
                printf("\n\n\n");
                break;
            case 3:
                printf("\n[%s]: Bene, allora alla prossima! (invio)", game_name());
                getchar();
                exit(0);
            default:
                printf("\n[%s]: ERRORE! Scelta non valida!\n", game_name());
                break;
        }

    } else {

        // carica la partita

        printf("\n[%s]: Questi sono i file disponibili:\n", game_name());

        file = fopen_secure(make_path("savegame_files", ".bin"), "rb");
        fread(&numero_files, sizeof(int), 1, file);
        files = trova_nomi(file, numero_files);
        fclose(file);

        // i nomi letti vengono poi stampati perché l'utente possa scegliere
        for(k = 0; k < numero_files; k++) {
            printf("\n[%d] -> %s", k, files[k]);
        }

        printf("\n\n[%s]", nome_utente);
        scelta = get_int(": ", 0, numero_files - 1);

        // compone l'array con i dati raccolti
        file = fopen_secure(make_path(files[scelta], ".bin"), "rb");
        fread(&numero_profili, sizeof(int), 1, file);

        // alloca l'elenco di profili
        giocatori_veri = (ProfiloGiocatore *) calloc(numero_profili, sizeof(ProfiloGiocatore));
        if(giocatori_veri == NULL) {
            printf("\n\nERRORE! Allocazione fallita!");
            exit(-1);
        }

        leggi_giocatori(file, numero_profili, giocatori_veri);
        fread(&game, sizeof(int), 1, file);

        // se il file contiene una partita già in corso, le seguenti operazioni vengono svolte:
        if(game == true) {

            // numero giocatori e numero giocatori veri
            fread(&numero_giocatori, sizeof(int), 1, file);
            fread(&numero_giocatori_veri, sizeof(int), 1, file);


            // TROCVARE E RIFARE QUESTA FUNZIONE
            // rivedere le specifiche

            //giocatori = componi_elenco(numero_giocatori);


            // giocatori veri
            for(j = 0; j < numero_giocatori_veri; j++) {
                fread(&segnaposto, sizeof(int), 1, file);
                giocatori[giocatori_veri[segnaposto].index].p = &giocatori_veri[segnaposto];
            }

            // stato vitale dei giocatori
            for(j = 0; j < numero_giocatori; j++) {
                fread(&segnaposto, sizeof(int), 1, file);
                if(segnaposto == 0) {
                    giocatori[j].vivo = false;
                }
            }
        }





        fclose(file);

        // chiude il file
        free(files);

    }





    // INIZIO PARTITA



    // commentare e RIADATTARE

    if(game == false) {

        numero_giocatori = get_int("\n\nNumero giocatori: ", 16, 1000);

        // riempie la lista dei giocatori
        //giocatori = componi_elenco(numero_giocatori);


        printf("\n\nQuanti di questi %d profini vuoi usare: ", numero_profili);
        numero_giocatori_veri = get_int("", 0, numero_profili);

        prov = (Elenco *) calloc(sizeof(Elenco), numero_profili);
        if(prov == NULL) {
            printf("\nERRORE! Allocazione fallita!\n");
            exit(-1);
        }

        for(k = 0; k < numero_profili; k++) {
            prov[k].id = k;
            prov[k].p = &giocatori_veri[k];
        }


        // scelta del profilo al quale assegnare il giusto indice
        for(j = 0; j < numero_giocatori_veri; j++) {


            // debuggato, lascia stampa solo i profili non ancora scelti

            printf("\nProfili a disposizione:");

            for(i = 0; i < numero_profili; i++) {

                if(prov[i].p != NULL) {
                    printf("\n[%d] -> %s", i, prov[i].p->nome);
                }
            }


            // deebuggato, non puoi scegliere due volte lo stesso profilo

            do {
                scelta = get_int("\n\n[Tu]: ", 0, numero_giocatori_veri);
                if(prov[scelta].p == NULL) {
                    printf("\nQuesto giocatore e' gia' stato scelto!");
                }
            } while(prov[scelta].p == NULL);


            // debuggato, non puoi inserire lo stesso id per due profili

            do {
                scelto = false;
                printf("\nId di %s: ", prov[scelta].p->nome);
                id = get_int("", 0, numero_giocatori);
                if(giocatori[id].p == NULL) {
                    giocatori_veri[scelta].index = id;
                    giocatori[id].p = &giocatori_veri[scelta];
                } else {
                    printf("\nQuesto id e' gia' preso, inseriscine un altro...");
                    scelto = true;
                }
            } while(scelto == true);

            prov[scelta].p = NULL;
        }

        free(prov);
    }








    // stampa la lista dei giocatori
    //stampa_lista_giocatori(&giocatori[0], numero_giocatori);

    // stampa i profili giocatore

    printf("\n\n");
    for(i = 0; i < numero_profili; i++) {

        printf("\n[%d] -> %s", giocatori_veri[i].index, giocatori_veri[i].nome);
    }





    // scrematura




    free(giocatori);
    free(giocatori_veri);












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


    // scrematura




    // svolgimento




    // finale



    return 0;
}



