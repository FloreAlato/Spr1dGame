//
// Created by Dando on 9/22/2022.
//

#ifndef DAVIDE_FLORE_66174_FILE_H
#define DAVIDE_FLORE_66174_FILE_H

#endif //DAVIDE_FLORE_66174_FILE_H



#include "main.h"



char names[4][32] = {
        "savegame_Nplayers_game",
        "savegame_Nplayers_noGame",
        "savegame_twoPlayers_game",
        "savegame_twoPlayers_noGame"
};









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

void scrivi_giocatori(FILE *file, int num, ProfiloGiocatore *giocatori) {

    for(int i = 0; i < num; i++) {
        fwrite(&giocatori[i].index, sizeof(int), 1, file);
        fwrite(&giocatori[i].nome, sizeof(char), 64, file);
        fwrite(&giocatori[i].spr1d_game_giocati, sizeof(int), 1, file);
        fwrite(&giocatori[i].spr1d_game_vinti, sizeof(int), 1, file);
        fwrite(&giocatori[i].finali_giocate, sizeof(int), 1, file);
        fwrite(&giocatori[i].giochi_giocati, sizeof(int), 1, file);
        fwrite(&giocatori[i].giochi_vinti, sizeof(int), 1, file);
    }
}







FILE *fopen_secure(char *filename, char *mode) {

    FILE *file = NULL;
    file = fopen(filename, mode);
    if(file == NULL) {
        printf("\n\nERRORE! Impossibile aprire file!");
        exit(-1);
    }

    return file;
}







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






char **trova_nomi(FILE *file, int numero) {

    char **nomi = NULL;

    nomi = (char **) calloc(numero, sizeof(char *));
    if(nomi == NULL) {
        printf("\n\nERRORE! Allocazione fallita!\n\n");
        exit(-1);
    }

    for(int k = 0; k < numero; k++) {
        nomi[k] = (char *) calloc(sizeof(char), 32);
        if(nomi[k] == NULL) {
            printf("\n\nERRORE! Allocazione fallita!\n\n");
            exit(-1);
        }

        fread(nomi[k], sizeof(char), 32, file);
    }

    return nomi;
}





void save(int *numero_profili, ProfiloGiocatore *players, bool *game, char *filename, int *numero_giocatori, int *numero_giocatori_veri, Elenco *gamers) {

    int i;
    FILE *file = NULL;

    file = fopen_secure(make_path(filename, ".bin"), "wb");

    fwrite(numero_profili, sizeof(int), 1, file);
    scrivi_giocatori(file, *numero_profili, players);
    fwrite(game, sizeof(int), 1, file);

    if(game) {
        // resto
        fwrite(numero_giocatori, sizeof(int), 1, file);
        fwrite(numero_giocatori_veri, sizeof(int), 1, file);
        for(i = 0; i < *numero_giocatori_veri; i++) {
            if(players[i].index >= 0) {
                fwrite(&players[i].index, sizeof(int), 1, file);
            }
        }
        for(i = 0; i < *numero_giocatori; i++) {
            fwrite(&gamers[i].vivo, sizeof(int), 1, file);
        }
    }

    fclose(file);
}







void add_file(char *newname) {

    FILE *file = NULL;
    int many, n;
    char **filenames = NULL;

    file = fopen_secure(make_path("savegame_files", ".bin"), "rb");

    fread(&many, sizeof(int), 1, file);

    filenames = trova_nomi(file, many);

    fclose(file);





    many++;


    file = fopen_secure(make_path("savegame_files", ".bin"), "wb");

    fwrite(&many, sizeof(int), 1, file);

    for(n = 0; n < many - 1; n++) {
        fwrite(filenames[n], sizeof(char), 32, file);
    }
    fwrite(newname, sizeof(char), 32, file);

    fclose(file);



    free(filenames);
}






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

