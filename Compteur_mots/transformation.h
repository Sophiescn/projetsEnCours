/*
    Auteur       : BENESBY Quentin / COUSSON Sophie
    Creation     : 15-03-2022
    Modification : 21-03-2022
*/

/* transformation.h */

#ifndef __transformation__
#define __transformation__

    #define TAILLE 32

    typedef struct mot {
        char* m;
        struct mot* mot_suivant;
        struct mot* mot_precedent;
    } Mot;

    typedef struct dictionnaire {
        char* m;
        int nb_occurences;
        struct dictionnaire* mot_suivant;
    } Dictionnaire;

    Mot* allocation_cellule(char* mot);
    Dictionnaire* initialisation_dictionnaire(char* mot);
    int cherche_incremente(char* mot, Dictionnaire* d);
    Dictionnaire* ajoute_dico(Dictionnaire* d, char* mot);
    Dictionnaire* mot_a_dictionnaire_1(Dictionnaire* d, Mot* m);
    Mot* empilement_cellule(Mot* liste, char* mot);
    void affichage_mot(Mot* mot);
    int mot_valide(char* mot);
    Mot* ajoute_liste(char* chaine);
    int longueur(Dictionnaire d);
    void remplit_chaine(char* arrive, int l, char* depart);
    void affichage_dico(Dictionnaire* d);
    Mot* renverse_liste(Mot* liste);

#endif
