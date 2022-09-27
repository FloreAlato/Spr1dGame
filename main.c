#include "svolgimento.h"









int main() {


    int numero_totale = 5;

    ProfiloGiocatore players[] = {
            0,
            "mannaggia",
            0,
            0,
            0,
            0,
            0,
            0,
            "hehe",
            0,
            0,
            0,
            0,
            0,
            0,
            "purucchio",
            0,
            0,
            0,
            0,
            0,
            0,
            "merenghe",
            0,
            0,
            0,
            0,
            0,
            0,
            "sos",
            0,
            0,
            0,
            0,
            0,
    };

    //save(&numero_totale, &players[0], false, "ciabatto");
    //add_file("ciabatto");


    //restore();


    //return 0;





    // TESTING

    srand(time(NULL));




    // TESTING
    int i, j, k, l, counter;

    int numero_giocatori = 0, numero_giocatori_veri = 0;
    Elenco *giocatori = NULL;
    ProfiloGiocatore *giocatori_veri;
    FILE *file = NULL;

    bool nuovo, esistente, scelto, is_game = false;
    int scelta, prosegui;
    char nome_giocatore[32];
    char opzioni[2][10] = {"carica", "inserisci"};
    char scelte[4][10] = {"continua", "salva", "inizia", "esci"};
    char **files = NULL;
    int numero_files;
    int numero_profili;

    int id, segnaposto;
    Elenco *prov = NULL;

    Elenco *lista_scremata = NULL;
    Elenco finale[2];

    int controllo[2] = {0, 0};
    bool finito = false;
    int winner;






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
    getchar();

    for(i = 1; i < PAGE_SIZE + 5; i++) {
        printf("\n%d", i);
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
            giocatori_veri[numero_profili - 1].index = -1;
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
                save(&numero_profili, giocatori_veri, false, nome_giocatore, NULL, NULL, NULL);
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
        fread(&is_game, sizeof(int), 1, file);

        // se il file contiene una partita già in corso, le seguenti operazioni vengono svolte:
        if(is_game == true) {

            // numero giocatori e numero giocatori veri
            fread(&numero_giocatori, sizeof(int), 1, file);
            fread(&numero_giocatori_veri, sizeof(int), 1, file);

            giocatori = componi_elenco(numero_giocatori);

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
                } else {
                    giocatori[j].vivo = true;
                }
            }
        }




        // chiude il file
        fclose(file);

        // libera l'array di nomi
        free(files);

    }


    // INIZIO PARTITA



    // solo se la partita non è cominciata
    if(is_game == false) {

        printf("\n\n[%s]: Numero giocatori\n[%s]", game_name(), nome_utente);
        numero_giocatori = get_int(": ", 16, 1000);

        // riempie la lista dei giocatori
        giocatori = componi_elenco(numero_giocatori);

        // chiede quanti profili usare
        printf("\n\n[%s]: Quanti di questi %d profini vuoi usare?\n[%s]", game_name(), numero_profili, nome_utente);
        numero_giocatori_veri = get_int(": ", 0, numero_profili);

        // array provvisoria, per riempire
        prov = (Elenco *) calloc(numero_profili, sizeof(Elenco));
        if(prov == NULL) {
            printf("\n\nERRORE! Allocazione fallita!\n\n");
            exit(-1);
        }

        // riempie l'array provvisoria
        for(k = 0; k < numero_profili; k++) {
            prov[k].id = k;
            prov[k].p = &giocatori_veri[k];
        }

        // scelta del profilo al quale assegnare il giusto indice
        for(j = 0; j < numero_giocatori_veri; j++) {

            // stampa i profili non ancora scelti
            printf("\n[%s]: Profili a disposizione:", game_name());

            for(i = 0; i < numero_profili; i++) {
                if(prov[i].p != NULL) {
                    printf("\n[%d] -> %s", i, prov[i].p->nome);
                }
            }

            // ogni profilo può essere scelto solo una volta
            do {
                printf("\n\n[%s]", nome_utente);
                scelta = get_int(": ", 0, numero_giocatori_veri);
                if(prov[scelta].p == NULL) {
                    printf("\n[%s]: Questo giocatore e' gia' stato scelto!", game_name());
                }
            } while(prov[scelta].p == NULL);


            // debuggato, non puoi inserire lo stesso id per due profili
            do {
                scelto = false;
                printf("\n[%s]: Id di %s\n[%s]", game_name(), prov[scelta].p->nome, nome_utente);
                id = get_int(": ", 0, numero_giocatori);
                if(giocatori[id].p == NULL) {
                    giocatori_veri[scelta].index = id;
                    giocatori[id].p = &giocatori_veri[scelta];
                } else {
                    printf("\n[%s]: Questo id e' gia' preso, inseriscine un altro...", game_name());
                    scelto = true;
                }
            } while(scelto == true);

            // segna che il profilo è stato scelto
            prov[scelta].p = NULL;
        }

        // l'array non serve più
        free(prov);
    }








    // STAMPA DEI GIOCATORI PER DEBUG



    // stampa la lista dei giocatori
    printf("\n\n");
    for(i = 0; i < numero_giocatori; i++) {
        printf("[%s] -> %d\n", print_player(giocatori[i]), giocatori[i].vivo);
    }

    // stampa i profili giocatore
    printf("\n\n");
    for(i = 0; i < numero_profili; i++) {

        printf("\n[%d] -> %s", giocatori_veri[i].index, giocatori_veri[i].nome);
    }
    getchar();
    getchar();


    // scrematura
    if(!is_game) {
        lista_scremata = scrematura(&giocatori[0], numero_giocatori);

        // stanno iniziando a giocare, quindi aumento la statistica
        for(i = 0; i < numero_giocatori; i++) {
            if(is_player(giocatori[i])) {
                giocatori[i].p->spr1d_game_giocati++;
            }
        }

        svolgimento(giocatori, numero_giocatori, finale, nome_utente, &numero_profili, giocatori_veri, &numero_giocatori, &numero_giocatori_veri);

    } else {
        printf("\n\n[%s]: Questa partita ha gia' svolto la scrematura iniziale\n\n", game_name());

        // controlla quanti giocatori vivi / utente sono rimasti
        superstiti(giocatori, numero_giocatori, controllo);



        if(controllo[1] == 0) {
            // finisci la partita con uno a caso
            // controlla quanti ce ne sono rimasti
            printf("[%s]: I giocatori rimasti sono tutti controllati dalla CPU!", game_name());
            printf("[%s]: Dunque il vincitore verra' scelto a caso fra i sopravvissuti!", game_name());

            do {
                segnaposto = rand_int(0, numero_giocatori);
            } while(!giocatori[segnaposto].vivo);

            // Frontman dello Spr1d Game
            for(i = 0; i < numero_giocatori; i++) {
                if(frontman(giocatori[i])) {
                    segnaposto = i;
                    giocatori[i].p->spr1d_game_vinti++;
                }
            }

            printf("\n\n\n\n\n[%s]: I GIOCHI SI CONCLUDONO, E IL VINCITORE E' %s!!!!!!!!!!\n\n", game_name(), print_player(giocatori[segnaposto]));

            // aggiorna le statistiche del giocatore, se si tratta di un profilo utente
            if(is_player(giocatori[segnaposto]) && !frontman(giocatori[segnaposto])) {
                giocatori[segnaposto].p->spr1d_game_vinti++;
            }

            getchar();

            free(giocatori);
            free(giocatori_veri);
            free(lista_scremata);
            return 0;

        } else if(controllo[0] == 2) {
            // passa direttamente alla fase finale
            // ottenendo prima la coppia rimanente

            // cerca i 2 giocatori vivi e li mette nel duo finale, si ferma appena trova il secondo
            i = 0, counter = 0;
            while(!finito) {
                if(giocatori[i].vivo) {
                    finale[counter] = giocatori[i];
                    counter++;
                } else if(counter > 1) {
                    finito = true;
                }

                i++;
            }

            // GIOCA A BLACKJACK CON LA COPPIA FINALE
            winner = black_jack(finale);
            printf("\n\n\n\n\n[%s]: I GIOCHI SI CONCLUDONO, E IL VINCITORE E' %s!!!!!!!!!!\n\n", game_name(), print_player(finale[winner]));

        } else {
            // avvia lo svolgimento e riducili a 2
            // ottieni così di nuovo gli ultimi 2
            lista_scremata = (Elenco *) malloc(sizeof(Elenco) * controllo[0]);
            if(lista_scremata == NULL) {
                printf("\nERRORE! Allocazione fallita!\n");
                exit(-1);
            }

            // riempila con i giocatori vivi
            i = 0, counter = 0;
            while(i < numero_giocatori & counter < controllo[0]) {
                if(giocatori[i].vivo) {
                    lista_scremata[counter] = giocatori[i];
                    counter++;
                }

                i++;
            }

            // SCRIVI FUNZIONE SVOLGIMENTO E METTILA QUI
            svolgimento(giocatori, numero_giocatori, finale, nome_utente, &numero_profili, giocatori_veri, &numero_giocatori, &numero_giocatori_veri);
        }
    }


    // svolgimento



    // finale
    winner = black_jack(finale);

    for(i = 0; i < 2; i++) {
        if(frontman(finale[i])) {
            winner = i;
            giocatori[finale[(int)!(bool)i].id].vivo = false;
            finale[i].p->spr1d_game_vinti++;
        }
    }

    printf("\n[%s]: LA PARTITA SI CONCLUDE CON LA VITTORIA DI %s!!!!!!!!", game_name(), print_player(finale[winner]));



    free(giocatori);
    free(giocatori_veri);
    free(lista_scremata);


    return 0;
}




