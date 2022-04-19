/*
    Auteur       : BENESBY Quentin / COUSSON Sophie
    Creation     : 29-03-2022
    Modification : 04-04-2022
*/

#include "case.h"
#include "affichage.h"

Case coordonnees_vers_case(int x,int y) {
    int dx, dy;
    dx = DECALAGE_X + 7;
    dy = DECALAGE_Y;

    x = -(x - dx) * 8;
    y = (y - dy) / 2;
    return x + y;
}
