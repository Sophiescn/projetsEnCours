/*
    Auteur       : BENESBY Quentin / COUSSON Sophie
    Creation     : 22-03-2022
    Modification : 28-03-2022
*/

#include "affichage.h"
#include "partie.h"
#include <ncurses.h>
#include <string.h>

void surligne_case(Grille g, int x, int y, char lettre, int etat) {
    if (!etat){
        mvprintw(x, y, " %c ", lettre);
    } else if (etat == 1) {
        attron(COLOR_PAIR(1));
        mvprintw(x, y, " %c ", lettre);
        attroff(COLOR_PAIR(1));
    } else {
        attron(COLOR_PAIR(2));
        mvprintw(x, y, " %c ", lettre);
        attroff(COLOR_PAIR(2));
    }
    
}

void affichage_grille(Grille g) {
    int i, j;
    int pos_x, pos_y;
    pos_y = (LINES / 2) - (TAILLE_GRILLE / 2);
    
    for (i = 0; i < TAILLE_GRILLE; i++) {
        pos_x = (COLS / 2) - (TAILLE_GRILLE / 2);
        for (j = 0; j < TAILLE_GRILLE; j++) {
            surligne_case(g, pos_y, pos_x, g.tab[i][j], g.etats[i][j]);
            pos_x += 3;
        }
        pos_y++;
    }
}

void affichage_aide() {
    char* chaine1, *chaine2, *chaine3;
    int decalage;
    chaine1 = "Guide des couleurs :";
    chaine2 = "Le vert pour une lettre selectionée";
    chaine3 = "le bleu pour une lettre qui ne l'est pas encore";
    decalage = COLS-strlen(chaine3);

    mvprintw(1, decalage, "%s", chaine1);
    mvprintw(2, decalage, "%s", chaine2);
    mvprintw(3, decalage, "%s", chaine3);
}

void affichage_score(int score) {
    int pos_x, pos_y;
    char chaine[16];
    
    sprintf(chaine, "%s : %d", "score", score);
    pos_x = (LINES/2) - ((strlen(chaine)) / 2);
    pos_y = COLS/2 - (TAILLE_GRILLE/2);
    attron(COLOR_PAIR(3));
    mvprintw(pos_x, pos_y, "%s", chaine);
    attroff(COLOR_PAIR(3));
}

void affichage_essais(int essais) {
    int pos_x, pos_y;
    char chaine[16];
    
    sprintf(chaine, "%s : %d", "essais", essais);
    pos_x = (LINES/2) + ((strlen(chaine)) / 2 - 1);
    pos_y = COLS/2 - (TAILLE_GRILLE/2);
    attron(COLOR_PAIR(3));
    mvprintw(pos_x, pos_y, "%s", chaine);
    attroff(COLOR_PAIR(3));
}

void affiche(Partie p) {
    affichage_grille(p.grille);
    affichage_aide();
    affichage_score(p.score);
    affichage_essais(p.essais);
    refresh();
}
