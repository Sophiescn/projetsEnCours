/*
    Auteur       : BENESBY Quentin / COUSSON Sophie
    Creation     : 15-03-2022
    Modification : 21-03-2022
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "transformation.h"

Mot* allocation_cellule(char* mot) {
    Mot* cellule;
    cellule = (Mot*) malloc(sizeof(Mot));
    if (cellule) {
        cellule->mot_suivant = NULL;
        cellule->mot_precedent = NULL;
        cellule->m = mot;
    }
    return cellule;
}

Dictionnaire* initialisation_dictionnaire(char* mot) {
    Dictionnaire* d;
    d = (Dictionnaire*) malloc(sizeof(Dictionnaire));
    if (!d){return d;}
    d->m = mot;
    d->nb_occurences = 1;
    d->mot_suivant = NULL;
    return d;
}

int cherche_incremente(char* mot, Dictionnaire* d) {
    Dictionnaire* dico;
    dico = d;
    while(dico){
        if (!strcmp(dico->m , mot)) {
            dico->nb_occurences++;
            return 1;
        }
        dico = dico->mot_suivant;
    }
    return 0;
}

Dictionnaire* ajoute_a_dico(Dictionnaire* d, char* mot) {
    Dictionnaire* temp;
    temp = initialisation_dictionnaire(mot);
    temp->mot_suivant = d;
    return temp;
}

Mot* empilement_cellule(Mot* liste, char* mot) {
    Mot* cellule;
    cellule = allocation_cellule(mot);

    if (!liste) {
        liste = cellule;
        return liste;
    }

    cellule->mot_suivant = liste;
    liste->mot_precedent = cellule;
    return cellule;
}

void affichage_mot(Mot* mot) {
    Mot* courant;
    courant = mot;
    while (courant) {
        printf("%s ", courant->m);
        courant = courant->mot_suivant;
    }
    printf("\n");
}

int mot_valide(char* mot) {
    int i;

    for (i = 0; i < strlen(mot); i++) {
        if (97 > mot[i] || mot[i] > 122) {
            return 0;
        }
    }
    return 1;
}

Mot* ajoute_liste(char* chaine) {
    Mot* cellule = NULL;
    int i, cmpt = 0;
    char* mot;

    mot = (char*) malloc(sizeof(char) * TAILLE);


    for (i = 0; i < strlen(chaine); i++) {
        if (chaine[i] == ' ' || chaine[i] == '\n') {
            mot[cmpt] = '\0';
            cmpt = 0;
            if (mot_valide(mot)) {
                cellule = empilement_cellule(cellule, mot);
            }
            mot = (char*) malloc(sizeof(char) * TAILLE);
            continue;
        }
        if (65 <= chaine[i] && chaine[i] <= 90) {
            mot[cmpt] = chaine[i] + 32;
        } else {
            mot[cmpt] = chaine[i];
        }
        cmpt++;
    }
    return cellule;
}

int longueur(Dictionnaire d) {
    Dictionnaire* courant;
    int l;
    l = 0;
    courant = &d;
    while(courant) {
        if (strlen(courant->m) > l) {
            l = strlen(courant->m);
        }
        courant = courant->mot_suivant;
    }
    return l;
}

void remplit_chaine(char* arrive, int l, char* depart) {
    int i;
    for (i = 0; i < strlen(depart); i++) {
        arrive[i] = depart[i];
    }
    for (;i < l; i++) {
        arrive[i] = ' ';
    }
    arrive[i] = '\0';
}

void affichage_dico(Dictionnaire* d) {
    Dictionnaire* courant;
    int longueur_max;
    char chaine[64];

    longueur_max = longueur(*d);
    courant = d;
    while (courant) {
        remplit_chaine(chaine, longueur_max, courant->m);
        printf("%s %d\n", chaine, courant->nb_occurences);
        courant = courant->mot_suivant;
    }
}

Dictionnaire* mot_a_dictionnaire_1(Dictionnaire* d, Mot* m) {
    Mot* courant;
    Dictionnaire* temp;
    courant = m;
    temp = d;
    while (courant) {
        
        if (!cherche_incremente(courant->m, temp)) {
            temp = ajoute_a_dico(temp, courant->m);
        }
        courant = courant->mot_suivant;
    }
    return temp;
}

Mot* renverse_liste(Mot* liste) {
    Mot* nouvelle;
    Mot* temp;
    nouvelle = NULL;
    temp = liste;

    while (temp) {
        nouvelle = empilement_cellule(nouvelle, temp->m);
        temp = temp->mot_suivant;
    }
    return nouvelle;
}
