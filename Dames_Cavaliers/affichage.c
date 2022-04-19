/*
    Auteur       : BENESBY Quentin / COUSSON Sophie
    Creation     : 29-03-2022
    Modification : 04-04-2022
*/

#include "affichage.h"
#include <string.h>
#include <unistd.h>
#include <ncurses.h>

int afficher_position(Position pos, char c) {
    int i;
    int cmpt;
    int place = DECALAGE_X;
    for (i = 63; i >= 0; i-=8) {
        move(place, DECALAGE_Y);
        for (cmpt = 8; cmpt > 0; cmpt--) {
            if ((pos.tableau >> (i - cmpt + 1)) & 1) {
                if (c == 'd') {
                    printw("+ ");
                } else if (c == 'c') {
                    printw("c ");
                }
            } else {
                printw(". ");
            }
        }
        place++;
    }
    return 0;
}

void affichage_mixte(Position dames, Position cavaliers) {
    int i;
    int cmpt;
    int place = DECALAGE_X;
    for (i = 63; i >= 0; i-=8) {
        move(place, DECALAGE_Y);
        for (cmpt = 8; cmpt > 0; cmpt--) {
            if ((dames.tableau >> (i - cmpt + 1)) & 1) {
                printw("+ ");
            } else if ((cavaliers.tableau >> (i - cmpt + 1)) & 1) {
                printw("c ");
            } else {
                printw(". ");
            }
        }
        place++;
    }
}

void affichage_binaire(unsigned long long n) {
    int i;
    int cmpt = 0;
    for (i = 63; i >= 0; i--) {
        printw("%llu", (n >> i) & 1);
        cmpt++;
        if (cmpt == 8) {
            printw(" ");
            cmpt = 0;
        }
    }
}

int sur_grille(int x, int y) {
    return DECALAGE_X <= x && DECALAGE_X + 7 >= x && DECALAGE_Y <= y && DECALAGE_Y + 14 >= y;
}
