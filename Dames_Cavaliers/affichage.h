/* affichage.h */

/*
    Auteur       : BENESBY Quentin / COUSSON Sophie
    Creation     : 29-03-2022
    Modification : 04-04-2022
*/

#ifndef __affichage__
#define __affichage__

    #include "position.h"
    #include <ncurses.h>

    #define DECALAGE_Y (COLS / 2 - 8 / 2)
    #define DECALAGE_X (LINES / 2 - 8 / 2)

    void affichage_binaire(unsigned long long n);
    int afficher_position(Position pos, char c);
    void affichage_mixte(Position dames, Position cavaliers);
    int sur_grille(int x, int y);

#endif
