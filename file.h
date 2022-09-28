//
// Created by Dando on 9/22/2022.
//

#ifndef DAVIDE_FLORE_66174_FILE_H
#define DAVIDE_FLORE_66174_FILE_H

#endif //DAVIDE_FLORE_66174_FILE_H



#include "main.h"



// nomi dei file di default, nel caso fasessi casino e servisse un reset
char names[4][32] = {
        "savegame_Nplayers_game",
        "savegame_Nplayers_noGame",
        "savegame_twoPlayers_game",
        "savegame_twoPlayers_noGame"
};








// funzione che legge un array di ProfiloGiocatore da un file
// prende in input il puntatore a file, quello all'array da leggere, e la sua dimensione
void leggi_giocatori(FILE *file, int num, ProfiloGiocatore *player) {

    for(int i = 0; i < num; i++) {
        fread(&player[i].index, sizeof(int), 1, file);
        fread(&player[i].nome, sizeof(char), 64, file);
        fread(&player[i].spr1d_game_giocati, sizeof(int), 1, file);
        fread(&player[i].spr1d_game_vinti, sizeof(int), 1, file);
        fread(&player[i].finali_giocate, sizeof(int), 1, file);
        fread(&player[i].giochi_giocati, sizeof(int), 1, file);
        fread(&player[i].giochi_vinti, sizeof(int), 1, file);
    }
}

// funzione che scrive un array di profili giocatore in un file
// prende in input un puntatore a file, un array di ProfiloGiocatore e la sua dimensione
// uguale alla precedente, ma con fwrite() al posto di fread()
void scrivi_giocatori(FILE *file, int num, ProfiloGiocatore *player) {

    for(int i = 0; i < num; i++) {
        fwrite(&player[i].index, sizeof(int), 1, file);
        fwrite(&player[i].nome, sizeof(char), 64, file);
        fwrite(&player[i].spr1d_game_giocati, sizeof(int), 1, file);
        fwrite(&player[i].spr1d_game_vinti, sizeof(int), 1, file);
        fwrite(&player[i].finali_giocate, sizeof(int), 1, file);
        fwrite(&player[i].giochi_giocati, sizeof(int), 1, file);
        fwrite(&player[i].giochi_vinti, sizeof(int), 1, file);
    }
}




// funzione per aprirre un file in modo sicuro
// l'ho scritta per non dover riscrivere ogni volta il debug dell'apertura di un file
// orende in input il nome del file da aprire e la modalità di apertura e restituisce il puntatore al file aperto
FILE *fopen_secure(char *filename, char *mode) {

    FILE *file = NULL;
    file = fopen(filename, mode);
    if(file == NULL) {
        printf("\nERRORE! Impossibile aprire il file!\n");
        exit(-1);
    }

    return file;
}




// similmente alla precedente, questa funzione serve a risparmiare tempo e ad avere un codice più leggibile
// prende in input una stringa e un'estensione, e restituisce una stringa con il path per aprire il file desidersto
char *make_path(char filename[], char extention[]) {

    char *path = NULL;

    path = (char *) calloc(63, sizeof(char));
    if(path == NULL) {
        printf("\n\nERRORE! Allocazione fallita!");
        exit(-1);
    }

    strcpy(path, "../cmake-build-debug/Save_Files/");
    strcat(path, filename);
    strcat(path, extention);

    return path;
}




// questa funzione serve a leggere da un file un array di char[32] di lunghezza numero
// prende un puntatore a file, in intero e restituisce una matrice di caratteri (o un array di stringhe, se preferisci)
// il puntatore a file deve puntare a un file già aperto
char **trova_nomi(FILE *file, int numero) {

    char **nomi = NULL;

    // alloca la matrice
    nomi = (char **) calloc(numero, sizeof(char *));
    if(nomi == NULL) {
        printf("\n\nERRORE! Allocazione fallita!\n\n");
        exit(-1);
    }
    // alloca le singole stringhe
    for(int k = 0; k < numero; k++) {
        nomi[k] = (char *) calloc(sizeof(char), 32);
        if(nomi[k] == NULL) {
            printf("\n\nERRORE! Allocazione fallita!\n\n");
            exit(-1);
        }

        // legge le stringhe dal file
        fread(nomi[k], sizeof(char), 32, file);
    }

    // infine ritorna la matrice
    return nomi;
}





// salva la partita, che il gioco sia iniziato o meno
// prende in input solo il puntatore allo stato della partita e il nome del file da aprire
// questo perchè gli altri dati sono in main.h, condivisi fra tutti gli header
void save(bool *game, char *filename) {

    int i;
    FILE *file = NULL;

    // apre il file con fopen_secure()
    file = fopen_secure(make_path(filename, ".bin"), "wb");

    // scrive il numero dei profili, l'array con i profili usando scrivi_giocatori() e lo stato della partita
    fwrite(&numero_giocatori_veri, sizeof(int), 1, file);
    scrivi_giocatori(file, numero_giocatori_veri, giocatori_veri);
    fwrite(game, sizeof(int), 1, file);

    if(game) {
        // se la partita è in corso, scrive anche il numero di giocatori
        // e il numero dei giocatori controllati dall'utente
        // e l'array con gli indici dei giocatori utente
        // e l'array con lo "stato vitale" di tutti i giocatori
        fwrite(&numero_giocatori, sizeof(int), 1, file);
        fwrite(&numero_giocatori_veri, sizeof(int), 1, file);
        for(i = 0; i < numero_giocatori_veri; i++) {
            if(giocatori_veri[i].index >= 0) {
                fwrite(&giocatori_veri[i].index, sizeof(int), 1, file);
            }
        }
        for(i = 0; i < numero_giocatori; i++) {
            fwrite(&giocatori[i].vivo, sizeof(int), 1, file);
        }
    }

    // chiude anche il file quando ha finito
    fclose(file);
}





// questa funzione aggiunge un nome alla lista dei file disponibili
// da usare insieme a save()
void add_file(char *newname) {

    FILE *file = NULL;
    int many, n;
    char **filenames = NULL;

    // apre il file dei file in lettura, legge il numero di file disponibili, i loro nomi, e chiude
    file = fopen_secure(make_path("savegame_files", ".bin"), "rb");
    fread(&many, sizeof(int), 1, file);
    filenames = trova_nomi(file, many);
    fclose(file);



    // incrementa il numero
    many++;

    // apre lo stesso file in scrittura, scrive il numero aggiornato, i nomi di prima, e il nuovo nome
    //poi chiude e libera l'array dei nomi
    file = fopen_secure(make_path("savegame_files", ".bin"), "wb");
    fwrite(&many, sizeof(int), 1, file);

    for(n = 0; n < many - 1; n++) {
        fwrite(filenames[n], sizeof(char), 32, file);
    }
    fwrite(newname, sizeof(char), 32, file);

    fclose(file);



    free(filenames);
}





// inutile, la usavo io per resettare i file
// la lascio qui come piccola chicca
void restore() {

    FILE *file = NULL;
    int i, num = 4;

    file = fopen_secure(make_path("savegame_files", ".bin"), "wb");

    fwrite(&num, sizeof(int), 1, file);
    for(i = 0; i < num; i++) {
        fwrite(&names[i], sizeof(char), 32, file);
    }

    fclose(file);
}

