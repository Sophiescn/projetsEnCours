/*
    Auteur       : BENESBY Quentin / COUSSON Sophie
    Creation     : 22-03-2022
    Modification : 28-03-2022
*/

#include "ouverture.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>


int lecture_fichier(char* nom, char** liste_mots) {
    FILE* fichier = NULL;
    char c;
    char* chaine;
    int cmpt1, cmpt2;

    
    fichier = fopen(nom, "r");
    chaine = (char*) malloc(sizeof(char) * TAILLE_MOT);
    assert(fichier);
    assert(chaine);
    cmpt1 = 0;
    cmpt2 = 0;
    while ((c = getc(fichier)) != EOF) {
        if (c != '\n') {
            chaine[cmpt1] = c;
            cmpt1++;
        } else {
            chaine[cmpt1] = '\0';
            if (strlen(chaine) >= 2){
                liste_mots[cmpt2] = (char*) malloc(sizeof(char) * TAILLE_MOT);
                strcpy(liste_mots[cmpt2], chaine);
                cmpt2++;
            }
            cmpt1 = 0;
        }
    }
    free(chaine);
    fclose(fichier);
    return cmpt2;
}

int recherche(char** liste_mots, char* mot, int taille) {
    int pos1, pos2, milieu, res;
    pos1 = 0;
    pos2 = taille;
    while (pos1 != pos2) {

        milieu = (pos1 + pos2) / 2;
        res = strcmp(liste_mots[milieu], mot);
        if (!res) {
            return 1;
        } else if (res > 0) {
            if (pos2 == milieu) {break;}
            pos2 = milieu;
        } else {
            if (pos1 == milieu) {break;}
            pos1 = milieu;
        }
    }
    return 0;
}
