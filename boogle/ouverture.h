/*
    Auteur       : BENESBY Quentin / COUSSON Sophie
    Creation     : 22-03-2022
    Modification : 28-03-2022
*/

/* ouverture.h */

#ifndef __ouverture__
#define __ouverture__

    #define TAILLE_MOT 64

    int lecture_fichier(char* nom, char** liste_mots);
    int recherche(char** liste_mots, char* mot, int taille);

#endif
