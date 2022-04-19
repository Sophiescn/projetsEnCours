/*
    Auteur       : BENESBY Quentin / COUSSON Sophie
    Creation     : 22-03-2022
    Modification : 28-03-2022
*/

/* affichage.h */

#ifndef __affichage__
#define __affichage__

    #include "grille.h"
    #include "partie.h"

    void surligne_case(Grille g, int x, int y, char lettre, int etat);
    void affichage_grille(Grille g);
    void affichage_aide();
    void affichage_score(int score);
    void affichage_essais(int essais);
    void affiche(Partie p);
#endif
