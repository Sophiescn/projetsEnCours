/*
    Auteur       : BENESBY Quentin / COUSSON Sophie
    Creation     : 22-03-2022
    Modification : 28-03-2022
*/

/* partie.h */

#ifndef __partie__
#define __partie__

    #include "grille.h"

    #define TAILLE_MOT 64

    typedef struct {
        Grille grille;
        int score;
        char** dictionnaire;
        int taille_dictionnaire;
        int essais;
    } Partie;

    typedef struct mot {
        char* m;
        struct mot* suivant;
    } Mot, * Trouve;

    typedef struct position {
        int x;
        int y;
        struct position* precedent;
    } Position;

    Partie initialise_partie(char** dictionnaire, int taille);
    int sur_grille(int dim_x, int dim_y, int pos_x, int pos_y);
    int lettre_valide(Position p, int pos_x, int pos_y, int taille_case);
    void selection_mots(Grille g, int pos_x, int pos_y);
    Mot* initialise_trouve(char* mot);
    void insere_tete_trouve(Trouve* L, char* mot);
    int est_dans_trouve(Trouve L, char* mot);
    void affiche_liste(Trouve L);
    Position* alloue_place(int x, int y);
    int position_vide(Position* p, int x, int y);
    int ajoute_position(Position** p, int x, int y);

#endif
