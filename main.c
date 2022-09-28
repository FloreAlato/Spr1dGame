#include "svolgimento.h"









int main() {

    srand(time(NULL));


    ProfiloGiocatore paolo = {
            0,
            "Paolo il Bello",
            0,
            0,
            0,
            0,
            0,
    };

    Elenco fin[2] = {
            0,
            true,
            &paolo,
            1,
            true,
            NULL
    };

    getchar();
    int d = tris(fin);
    getchar();




    return 0;




    // le variabili sono organizzate in ordine di apparizione o importanza

    // interi vari e puntatore per gestire i file
    int i, j, k, l, counter;
    FILE *file = NULL;

    // variabili per l'introduzione e la scelta dell'operazione
    bool nuovo, esistente, scelto, is_game = false;
    int scelta, prosegui;
    char nome_giocatore[32];
    char opzioni[2][10] = {"carica", "inserisci"};
    char scelte[4][10] = {"continua", "salva", "inizia", "esci"};
    char **files = NULL;
    int numero_files;
    int numero_profili;

    // variabili per il riempimento dell'array di giocatori
    int id, segnaposto;
    bool finito = false;
    Elenco *prov = NULL;

    // variabili per la scrematura
    Elenco *lista_scremata = NULL;
    Elenco finalisti[2];

    // variabili per lo svolgimento
    int controllo[2] = {0, 0};
    int winner, f_man = 3;
    Elenco *alternativa = NULL;

    // variabili per il salvataggio e la gestione degli utenti
    int numero_utenti;
    bool risposta;
    char **nomi = NULL;







    // LOGIN / CREAZIONE PROFILO UTENTE

    // in questa sezione il programma si occupa solo di introdursi all'utente, è solo estetica

    // controlla se l'utente ha mai usato il programma e salva la risposta nel booleano risposta
    // usa la funzione si_no()
    // si_no() -> main.h
    printf("[%s]: Hai mai usato questo programma? (si / no)", game_name());
    printf("\n[%s]", nome_utente);
    risposta = si_no(": ");
    getchar();

    // apre il file con i profili utente e recuepra i nomi di tutti i profili usati finora
    // usa la funzione fopen_secure() per velocizzare la scrittura del progetto
    // salva i nomi nell'array nomi usando la funzione trova_nomi() e il loro numero nell'intero numero_utenti
    // fopen_secure() -> file.h
    // trova_nomi() -> file.h
    file = fopen_secure(make_path("users", ".bin"), "rb");
    fread(&numero_utenti, sizeof(int), 1, file);
    nomi = trova_nomi(file, numero_utenti);
    fclose(file);

    // una volta ottenuta la risposta, decide cosa farne
    if(risposta) {
        // se l'utente ha già usato il programma, gli fa scegliere quale profilo usare
        printf("\n[%s]: Quale di questi e' il tuo nome?\n", game_name());
        for(i = 0; i < numero_utenti; i++) {
            printf("[%d] -> %s\n", i, nomi[i]);
        }

        // prende la risposta dell'utente sotto forma di intero usando la funzione get_int()
        // salva nella variabile nome_utente l'opzione scelta per usarla più tardi
        // get_int() -> main.h
        printf("\n[%s]", nome_utente);
        scelta = get_int(": ", 0, numero_utenti - 1);
        strcpy(nome_utente, nomi[scelta]);

    } else {
        // se l'utente non ha mai usato il programma, chiede il nome e so salva direttamente in nome_utente
        printf("\n[%s]: Bene allora, come vorresti chiamarti?\n[%s]: ", game_name(), nome_utente);
        scanf(" %s", nome_utente);
        getchar();

        // incrementa il numero di nomi utente
        numero_utenti++;

        // salva il nuovo nome nel file dei nomi usando fopen_secure()
        file = fopen_secure(make_path("users", ".bin"), "wb");
        fwrite(&numero_utenti, sizeof(int), 1, file);

        for(i = 0; i < numero_utenti - 1; i++) {
            fwrite(nomi[i], sizeof(char), 64, file);
        }
        fwrite(&nome_utente, sizeof(char), 64, file);

        fclose(file);
    }

    // l'array con i nomi utente è superflua, ce ne possiamo liberare
    free(nomi);






    // SETUP SCHERMO

    // questa sezione serve a regolare le dimensioni del terminale così da godersi al meglio i giochi

    // questa stampa introduce la prossima azione e il successo della precedente
    printf("\n\n[%s]: Perfetto, %s! E' il caso di fare un po' di setup", game_name(), nome_utente);
    printf("\n[%s]: Regola le dimensioni del terminale finche' non vedi il numero 25 (invio)", game_name());
    getchar();
    getchar();

    // lo schermo deve essere grande 25 righe
    for(i = 1; i < PAGE_SIZE + 5; i++) {
        printf("\n%d", i);
    }
    printf("\n[%s]: Ora che hai regolato lo schermo, premi invio per cominciare (invio)", game_name());
    getchar();








    // AVVIO PROGRAMMA, SCELTA DELL'OPERAZIONE

    // questa sezione differenzia le operazioni da svolgere per avviare il programma come da consegna


    // chiede all'utente se vuole caricare una partita esistente o inserire un profilo giocatore
    // salva la risposta nel booleano nuovo usando la funzione choice_sting()
    // choice_string() -> main.h
    printf("\n\n\n[%s]: Cosa vuoi fare? (carica / inserisci)\n[%s]", game_name(), nome_utente);
    nuovo = (bool)choice_string(": ", 2, opzioni);

    // differenzia le oerazioni
    if(nuovo) {
        // se l'utente vuole inserire un profilo, il numero_profili parte da 1
        // e l'array di 1 ProfiloGiocatore è allocata dinamicamente
        // ProfiloGiocatore -> main.h
        numero_profili = 1;
        giocatori_veri = (ProfiloGiocatore *) calloc(numero_profili, sizeof(ProfiloGiocatore));
        if(giocatori_veri == NULL) {
            printf("\n\nERRORE! Allocazione fallita!");
            exit(-1);
        }

        // segue un'iterazione che continua finchè l'utente vuole inserire nuovi profili
        do {

            // il programma sceglie se è il caso di riallocare l'array dei profili, per evitare passaggi inutili
            if(numero_profili > 1) {
                giocatori_veri = (ProfiloGiocatore *) realloc(giocatori_veri, sizeof(ProfiloGiocatore) * numero_profili);
            }

            // questa iterazione serve a impedire che l'utente inserisca nomi non univoci
            do {
                esistente = false;

                // il nome del profilo appena generato viene raccolto con una scanf
                printf("\n[%s]: Nome giocatore\n[%s]: ", game_name(), nome_utente);
                scanf (" %[^\n]%*c", nome_giocatore);

                // ed è poi confrontato con gli altri raccolti finora per evitare doppioni
                // se viene trovato un nome uguale, i ciclo si interrompe e il booleano esistente è settato a true
                for(i = 0; i < numero_profili; i++) {
                    if(strcmp(giocatori_veri[i].nome, nome_giocatore) == 0) {
                        esistente = true;
                        printf("\n\n[%s]: Hai gia' inserito questo nome\n\n", game_name());
                        break;
                    }
                }

                // il ciclo si ripete se viene trovato un nome uguale all'ultimo inserito
            } while(esistente == true);


            // tutti i campi del ProfiloGiocatore sono azzerati perchè la riallocazione non se ne occupa in automatico
            // tranne l'index, per chiarezza
            strcpy(giocatori_veri[numero_profili - 1].nome, nome_giocatore);
            giocatori_veri[numero_profili - 1].index = -1;
            giocatori_veri[numero_profili - 1].spr1d_game_giocati = 0;
            giocatori_veri[numero_profili - 1].spr1d_game_vinti = 0;
            giocatori_veri[numero_profili - 1].finali_giocate = 0;
            giocatori_veri[numero_profili - 1].giochi_giocati = 0;
            giocatori_veri[numero_profili - 1].giochi_vinti = 0;

            // poi il programma chiede all'utente quale operazione desidera svolgere e la salva nell'intero prosegui
            // fa ciò grazie alla funzione choice_string()
            // choice_string() -> main.h
            printf("\n[%s]: Scegli l'operazione: (continua / salva / inizia / esci)\n[%s]", game_name(), nome_utente);
            prosegui = choice_string(": ", 4, scelte);

            // il conteggio dei profili è incrementato ogni volta
            numero_profili++;

            // il ciclo si ripete se l'utente ha scelto di inserire un altro profilo
        } while(prosegui == 0);

        // a fine loop il numero_profili viene incrementato una volta di troppo, quindi va decrementato
        numero_profili--;






        // una volta finito di inserire profili, il programma usa l'intero raccolto per decidere cosa fare con i profili raccolti
        // fa questo con una swtch
        switch(prosegui) {
            case 1:
                // se l'utente vuole salvare i profili in un file senza partita, il programma raccoglie il nome del file
                // non esiste un vero e proprio controllo di univocità del nome, solo un avvertimento all'utente
                printf("\n[%s]: Inserisci il nome del file nel quale vorresti salvare i profili", game_name());
                printf("\n[%s]: (ATTENZIONE! Se inserirai il nome di un file esistente, questo verrà sovrascritto!)", game_name());

                // il nome viene salvato nella variabile nome_giocatore, riutilizzata per risparmiare simboli
                // non è un problema per il programma, visto che la stringa ha la dimensione giusta
                printf("\n\n[%s]: ", nome_utente);
                scanf(" %s", nome_giocatore);

                // la partita viene salvata nel file scelto con la funzione save()
                // e poi il nome viene aggiunto all'elenco di file di salvataggio con la funzione add_file()
                // save() -> file.h
                // add_file() -> file.h
                is_game = false;
                save(&is_game, nome_giocatore);
                add_file(nome_giocatore);
                break;
            case 2:
                // se l'utente sceglie di iniziare la partita, il programma mostra solo un messaggio di avvio
                // e aspetta l'input utente per far partire il gioco
                printf("\n\n\n[%s]: ALLORA COMINCIAMO!!!!! (invio)", game_name());
                getchar();
                printf("\n\n\n");
                break;
            case 3:
                // se l'utente vuole uscire dal gioco, il programma stampa un messaggio di avvio e arresta il programma
                printf("\n[%s]: Bene, allora alla prossima! (invio)", game_name());
                getchar();
                exit(0);
            default:
                // speriamo che questo messaggio non venga main stampato
                printf("\n[%s]: ERRORE! Scelta non valida!\n", game_name());
                break;
        }

    } else {
        // CARICA PARTITA

        // questi comandi vengono eseguiti se l'utente vuole caricare una partita da un file di salvataggio

        // il programma recupera i nomi dei file di salvataggio disponibili e li stampa perchè l'utente ne scelga uno
        // questo avviene grazie a fopen_secure() e trova_nomi()
        // trova_nomi() -> file.h
        printf("\n[%s]: Questi sono i file disponibili:\n", game_name());
        file = fopen_secure(make_path("savegame_files", ".bin"), "rb");
        fread(&numero_files, sizeof(int), 1, file);
        files = trova_nomi(file, numero_files);
        fclose(file);

        // i nomi letti sono stampati
        for(k = 0; k < numero_files; k++) {
            printf("\n[%d] -> %s", k, files[k]);
        }

        // la scelta viene raccolta tramite get_int()
        printf("\n\n[%s]", nome_utente);
        scelta = get_int(": ", 0, numero_files - 1);

        // il file scelto viene aperto e viene salvato il numero_profili
        file = fopen_secure(make_path(files[scelta], ".bin"), "rb");
        fread(&numero_profili, sizeof(int), 1, file);

        // il numero_profili è poi usato per allocare dinamicamente l'array di ProfiliGiocatore
        giocatori_veri = (ProfiloGiocatore *) calloc(numero_profili, sizeof(ProfiloGiocatore));
        if(giocatori_veri == NULL) {
            printf("\n\nERRORE! Allocazione fallita!");
            exit(-1);
        }

        // poi i giocatori sono letti dal file con la funzione leggi_giocatori()
        // e viene letto anche il booleano che indica se è in corso una partita
        // leggi_giocatori() -> file.h
        leggi_giocatori(file, numero_profili, giocatori_veri);
        fread(&is_game, sizeof(int), 1, file);

        // se il file contiene una partita già in corso, le seguenti operazioni vengono svolte
        if(is_game == true) {

            // il file recupera il numero di giocatori totali e quello di giocatori utente
            fread(&numero_giocatori, sizeof(int), 1, file);
            fread(&numero_giocatori_veri, sizeof(int), 1, file);

            // viene allocato l'elenco dei giocatori tramite la funzione componi_elenco()
            // componi_elenco() -> file.h
            giocatori = componi_elenco(numero_giocatori);

            // viene letto l'array di indici dei giocatori utente
            // e questi sono usati per collegare ogni profilo alla rispettiva posizione nell'elenco
            for(j = 0; j < numero_giocatori_veri; j++) {
                fread(&segnaposto, sizeof(int), 1, file);
                giocatori[giocatori_veri[segnaposto].index].p = &giocatori_veri[segnaposto];
            }

            // viene alche letto lo "stato vitale" dei giocatori, sia CPU che non
            for(j = 0; j < numero_giocatori; j++) {
                fread(&segnaposto, sizeof(int), 1, file);
                if(segnaposto == 0) {
                    giocatori[j].vivo = false;
                } else {
                    giocatori[j].vivo = true;
                }
            }
        }




        // ora possiamo chiudere il file
        fclose(file);

        // l'array con i nomi dei files non ha più motivo di esistere
        free(files);

    }





    // INIZIO PARTITA

    // questa sezione viene svolta solo nel caso di una partita non iniziata


    // se l'utente ha scelto di inserire manualmente i profili o di caricare un file che non ha una partita in corso
    if(is_game == false) {

        // il programma recupera dall'utente il numero totale dei giocatori con get_int()
        printf("\n\n[%s]: Numero giocatori\n[%s]", game_name(), nome_utente);
        numero_giocatori = get_int(": ", 16, 1000);

        // poi alloca l'Elenco dei giocatori con componi_elenco()
        giocatori = componi_elenco(numero_giocatori);

        // chiede all'utente quanti profili vuole usare e salva la risposta nell'intero numero_giocatori_veri
        printf("\n\n[%s]: Quanti di questi %d profini vuoi usare?\n[%s]", game_name(), numero_profili, nome_utente);
        numero_giocatori_veri = get_int(": ", 0, numero_profili);

        // alloca un Elenco provvisorio che servirà per il debug della scelta del profilo da usare
        // questa volta non serve azzerare i valori perchè calloc lo fa in automatico
        prov = (Elenco *) calloc(numero_profili, sizeof(Elenco));
        if(prov == NULL) {
            printf("\n\nERRORE! Allocazione fallita!\n\n");
            exit(-1);
        }

        // questo è riempito così da essere uguale al principale
        for(k = 0; k < numero_profili; k++) {
            prov[k].id = k;
            prov[k].p = &giocatori_veri[k];
        }

        // il programma itera per tante volte quanti profili ci sono da scegliere
        for(j = 0; j < numero_giocatori_veri; j++) {

            // stampa i profili non ancora scelti
            // capisce ciò perchè in profilo non scelto non è ancora collegato all'Elenco principale
            printf("\n[%s]: Profili a disposizione:", game_name());
            for(i = 0; i < numero_profili; i++) {
                if(prov[i].p != NULL) {
                    printf("\n[%d] -> %s", i, prov[i].p->nome);
                }
            }

            // quindi prende in input la scelta dell'utente e si accerta che sia univoca
            do {
                printf("\n\n[%s]", nome_utente);
                scelta = get_int(": ", 0, numero_giocatori_veri);
                if(prov[scelta].p == NULL) {
                    printf("\n[%s]: Questo giocatore e' gia' stato scelto!", game_name());
                }
            } while(prov[scelta].p == NULL);


            // poi fa decidere quale id assegnare ad ogni profilo
            // usa un metodo simile al precedente, accertandosi che il profilo non sia già collegato all'Elenco principale
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

            // il profilo viene poi "rimosso" dalla lista provvisoria
            prov[scelta].p = NULL;
        }

        // a fine inserimento la lista provvisoria non serve più
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










    // SCREMATURA

    // questa sezione è bella intricata, svolge la scrematura dei giocatori come consegna
    // ho dovuto sbatterci la testa per pensare ai casi nei quali il file caricato contenesse una scrematura incompleta



    // se il gioco non è cominciato, esegue la scrematura, altrimenti controlla quanti giocatori sono ancora in vita
    if(!is_game) {

        // CONTROLLA CHE SIANO TUTTI VIVI, ALTRIMENTI RIADATTA LA LISTA DI INPUT E IL NUMERO DI GIOCATORI TOTALI

        // qualora i giocatori non dovessero essere tutti vivi, occorre restringere l'Elenco dei giocatori da scremare
        // il numero di giocatori vivi viene calcolato con superstiti()
        // questa funzione salva il numero di giocatori vivi in controllo[0] e quello di giocatori utente vivi in controllo[1]
        // se sono tutti vivi, l'array Elenco lista_scremata viene ottenuta con la funzione scrematura()
        // superstiti() -> main.h
        // scrematura() -> scrematura.h
        superstiti(giocatori, numero_giocatori, controllo);
        if(controllo[0] == numero_giocatori) {
            lista_scremata = scrematura(giocatori, numero_giocatori, &superstiti_scrematura);

        } else {
            // se i giocatori non sono tutti vivi, viene allocata l'array alternativa
            // viene poi riempita con la funzione solo_vivi()
            // e infine questa nuova array viene scremata con scrematura()
            // solo_vivi() -> main.h
            alternativa = (Elenco *) malloc(sizeof(Elenco) * controllo[0]);
            if(alternativa == NULL) {
                printf("\nERRORE! Allocazione fallita!\n");
                exit(-1);
            }

            solo_vivi(alternativa, numero_giocatori, superstiti_scrematura);
            lista_scremata = scrematura(alternativa, controllo[0], &superstiti_scrematura);
        }

    } else {
        // se invece il gioco è già iniziato, si trovano i giocatori vivi con superstiti()
        superstiti(giocatori, numero_giocatori, controllo);

        // e si alloca una lista scremata piena di tutti i giocatori ancora in vita usando solo_vivi()
        superstiti_scrematura = controllo[0];
        lista_scremata = (Elenco *) malloc(superstiti_scrematura * sizeof(Elenco));
        if(lista_scremata == NULL) {
            printf("\nERRORE! Allocazione fallita!\n");
            exit(-1);
        }

        solo_vivi(lista_scremata, numero_giocatori, superstiti_scrematura);
    }


    // stampa le array per debug
    printf("\n\n\n\nTUTTI");
    for(i = 0; i < numero_giocatori; i++) {
        printf("\n[%s] - > %d", print_player(giocatori[i]), giocatori[i].vivo);
    }

    printf("\n\n\n\nAVANZI DI SCREMATURA (ne sono rimasti %d, di cui %d utenti)", superstiti_scrematura, controllo[1]);
    for(i = 0; i < superstiti_scrematura; i++) {
        printf("\n[%s] -> %d", print_player(lista_scremata[i]), lista_scremata[i].vivo);
    }

    getchar();
    getchar();









    // SVOLGIMENTO

    // in questa sezione avviene il gioco vero e proprio


    // se sono rimasti solo due giocatori in vita, si passa direttamente alla fase finale
    // questo avviene riempiendo la coppia che giocherà a blackjack
    if(superstiti_scrematura == 2) {
        finalisti[0] = lista_scremata[0];
        finalisti[1] = lista_scremata[1];

    } else if(superstiti_scrematura % 2 == 0) {
        // altrimenti la coppia viene riempita con la funzione svolgimento()
        //svolgimento() -> svolgimento.h
        svolgimento(lista_scremata, superstiti_scrematura, finalisti);

    } else {
        // ancora una volta, speriamo che questo messaggio non venga mai stampato
        printf("\n\n\n[%s]: QUALCOSA DEVE ESSERE ANDATO STORTO CON LA SCREMATURA!\n[%s]: ADDIO!", game_name(), game_name());
    }





    // FINALE

    // questa fase consiste solo di una partita a blackjack e tutti gli accorgimenti necessari per aggiornare le statistiche dei giocatori

    // aggiorna il conteggio finali_giocate se i finalisti sono utenti
    // salva inoltre la posizione di Riccardo Scateni se dovesse essere presente
    if(is_player(finalisti[0])) {
        finalisti[0].p->finali_giocate++;

        if(frontman(finalisti[0])) {
            f_man = 0;
        }
    }
    if(is_player(finalisti[1])) {
        finalisti[1].p->finali_giocate++;

        if(frontman(finalisti[1])) {
            f_man = 1;
        }
    }

    // gioca a blackjack e decide il vincitore
    printf("\n\n[%s]: Per il finale dei giochi, una partita a BlackJack!!! (invio)", game_name());
    winner = black_jack(finalisti);

    // Frontman dello Sprid Game
    if(f_man < 3) {
        winner = f_man;
    }

    // stampa il messaggio di fine gioco
    printf("\n\n\n\n[%s]: I GIOCHI SI CHIUDONO CON LA VITTORIA DI %s!!! (invio)", game_name(), print_player(finalisti[winner]));

    // aggiorna le vittorie
    if(is_player(finalisti[winner])) {
        finalisti[winner].p->spr1d_game_vinti++;
    }

    // chiede all'utente se vuole salvare la partita prima di uscire dal gioco
    // usa la funzione si_no()
    // si_no() -> main.h
    printf("\n[%s]: Vuoi salvare la partita? (si / no)\n[%s]", game_name(), nome_utente);
    scelta = (bool)si_no(": ");

    if(scelta) {
        printf("\n[%s]: Come vuoi chiamare il file di salvataggio? (ATTENZIONE, SE SCEGLI IL NOME DI UN FILE ESISTENTE, QUESTO VERRA' SOVRASCRITTO!)", game_name());
        scanf(" %s", nome_giocatore);

        // se l'utente sceglie di salvare, il programma usa la funzione save() e add_file(), ma stavolta per una partita iniziata
        is_game = true;
        save(&is_game, nome_giocatore);
        add_file(nome_giocatore);

        printf("\n[%s]: Bene, alla prossima allora!", game_name());
        return 0;

    } else {
        printf("\n[%s]: Alla prossima allora!", game_name());
        return 0;
    }

    // infine libera tutta la memoria inutile
    free(giocatori);
    free(giocatori_veri);
    free(lista_scremata);
    free(alternativa);
}




