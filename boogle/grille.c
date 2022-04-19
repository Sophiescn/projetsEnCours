/*
    Auteur       : BENESBY Quentin / COUSSON Sophie
    Creation     : 22-03-2022
    Modification : 28-03-2022
*/

#include "grille.h"
#include <stdlib.h>
#include <assert.h>

int caractere_aleatoire() {
    int rd;
    
    rd = rand() % 100;
    if (rd == 0) {
        return 106; /* J */
    } else if (rd <= 1) {
        return 107; /* K */
    } else if (rd <= 2) {
        return 113; /* Q */
    } else if (rd <= 3) {
        return 118; /* V */
    } else if (rd <= 4) {
        return 120; /* X */
    } else if (rd <= 5) {
        return 122; /* Z */
    } else if (rd <= 7) {
        return 98; /* B */
    } else if (rd <= 9) {
        return 102; /* F */
    } else if (rd <= 11) {
        return 103; /* G */
    } else if (rd <= 13) {
        return 112; /* P */
    } else if (rd <= 15) {
        return 119; /* W */
    } else if (rd <= 17) {
        return 121; /* Y */
    } else if (rd <= 20) {
        return 99; /* C */
    } else if (rd <= 23) {
        return 109; /* M */
    } else if (rd <= 26) {
        return 117; /* U */
    } else if (rd <= 30) {
        return 100; /* D */
    } else if (rd <= 34) {
        return 108; /* L */
    } else if (rd <= 39) {
        return 104; /* H */
    } else if (rd <= 45) {
        return 114; /* R */
    } else if (rd <= 52) {
        return 97; /* A */
    } else if (rd <= 59) {
        return 105; /* I */
    } else if (rd <= 66) {
        return 110; /* N */
    } else if (rd <= 73) {
        return 111; /* O */
    } else if (rd <= 80) {
        return 115; /* S */
    } else if (rd <= 88) {
        return 116; /* T */
    } else if (rd <= 99) {
        return 101; /* E */
    }
    return -1;
}

void remplir_grille(Grille* grille) {
    int i, j;

    for (i = 0; i < TAILLE_GRILLE; i++) {
        for (j = 0; j < TAILLE_GRILLE; j++) {
            grille->tab[i][j] = caractere_aleatoire() - 32;
        }
    }

    for (i = 0; i < TAILLE_GRILLE; i++) {
        for (j = 0; j < TAILLE_GRILLE; j++) {
            grille->etats[i][j] = 0;
        }
    }
}

char change_etat(Grille* grille, int x, int y, int etat) {
    grille->etats[y][x] = etat;
    return grille->tab[y][x];
}

void reinitialiser_etat(Grille* grille) {
    int i, j;

    assert(grille);
    for (i = 0; i < TAILLE_GRILLE; i++) {
        for (j = 0; j < TAILLE_GRILLE; j++) {
            grille->etats[i][j] = 0;
        }
    }
}
