#include "sauvegarde.h"
#include "monde.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>


int entier_fichier(char* chaine, int taille) {
    char entier[8];
    int i;
    i = 0;
    while (1) {
        if (chaine[i] == '\0') {
            break;
        }
        if (i >= taille) {
            entier[i-taille] = chaine[i];
        }
        i++;
    }
    return atoi(entier);
}


void lis_fichier(Partie* p) {
    FILE* f;
    char chaine[32];
    f = fopen("serpent.ini", "r");
    assert(f);
    while (fgets(chaine, 32, f)) {
        if (chaine[0] == 'l') {
            p->largeur = entier_fichier(chaine, 10);
        } else if (chaine[0] == 'h') {
            p->hauteur = entier_fichier(chaine, 10);
        } else if (chaine[0] == 'n') {
            p->nb_pommes = entier_fichier(chaine, 16);
        } else if (chaine[0] == 't') {
            p->taille_serp = entier_fichier(chaine, 17);
        } else if (chaine[0] == 'd') {
            p->raffraichissement = entier_fichier(chaine, 13);
        }
    }
}
