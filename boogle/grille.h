/*
    Auteur       : BENESBY Quentin / COUSSON Sophie
    Creation     : 22-03-2022
    Modification : 28-03-2022
*/

/* grille.h */

#ifndef __grille__
#define __grille__

    #include <stdio.h>
    #define TAILLE_GRILLE 4

    typedef struct {
        char tab[TAILLE_GRILLE][TAILLE_GRILLE];
        int etats[TAILLE_GRILLE][TAILLE_GRILLE];
    } Grille;

    int caractere_aleatoire();
    void remplir_grille(Grille* grille);
    char change_etat(Grille* grille, int x, int y, int etat);
    void reinitialiser_etat(Grille* grille);

#endif
