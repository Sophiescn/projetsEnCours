/*
    Auteur       : BENESBY Quentin / COUSSON Sophie
    Creation     : 29-03-2022
    Modification : 04-04-2022
*/

#include "menu.h"
#include <ncurses.h>

void affiche_menu(int select) {
    if (select == 1) {
        attron(COLOR_PAIR(1));
        mvprintw(0, 0, "1 - Demarrer");
        attroff(COLOR_PAIR(1));
        mvprintw(1, 0, "2 - Options");
        mvprintw(2, 0, "3 - Credits");
        mvprintw(3, 0, "4 - Quitter");
    } else if (select == 2) {
        mvprintw(0, 0, "1 - Demarrer");
        attron(COLOR_PAIR(1));
        mvprintw(1, 0, "2 - Options");
        attroff(COLOR_PAIR(1));
        mvprintw(2, 0, "3 - Credits");
        mvprintw(3, 0, "4 - Quitter");
    } else if (select == 3) {
        mvprintw(0, 0, "1 - Demarrer");
        mvprintw(1, 0, "2 - Options");
        attron(COLOR_PAIR(1));
        mvprintw(2, 0, "3 - Credits");
        attroff(COLOR_PAIR(1));
        mvprintw(3, 0, "4 - Quitter");
    } else if (select == 4) {
        mvprintw(0, 0, "1 - Demarrer");
        mvprintw(1, 0, "2 - Options");
        mvprintw(2, 0, "3 - Credits");
        attron(COLOR_PAIR(1));
        mvprintw(3, 0, "4 - Quitter");
        attroff(COLOR_PAIR(1));
    }
}

void affiche_options(int select) {
    if (select == 1) {
        attron(COLOR_PAIR(1));
        mvprintw(0, 0, "1 - Dames");
        attroff(COLOR_PAIR(1));
        mvprintw(1, 0, "2 - Cavaliers");
        mvprintw(2, 0, "3 - Dames Cavaliers");
    } else if (select == 2) {
        mvprintw(0, 0, "1 - Dames");
        attron(COLOR_PAIR(1));
        mvprintw(1, 0, "2 - Cavaliers");
        attroff(COLOR_PAIR(1));
        mvprintw(2, 0, "3 - Dames Cavaliers");
    } else if (select == 3) {
        mvprintw(0, 0, "1 - Dames");
        mvprintw(1, 0, "2 - Cavaliers");
        attron(COLOR_PAIR(1));
        mvprintw(2, 0, "3 - Dames Cavaliers");
        attroff(COLOR_PAIR(1));
    }
}

int choix_options() {
    int touche, option;
    option = 1;
    while (1) {
        touche = getch();
        if (touche != ERR) {
            if (touche == KEY_UP) {
                if (option != 1) {option--;}
                else {option = 3;}
            } else if (touche == KEY_DOWN) {
                if (option != 3) {option++;}
                else {option = 1;}
            } else if (touche == '\n') {
                break;
            }
        }
        affiche_options(option);
        refresh();
    }
    return option;
}

int choix(int choix, int* option) {
    if (choix == 1) {
        return 0;
    }
    if (choix == 2) {
        clear();
        *option = choix_options();
        clear();
        return 1;
    }
    if (choix == 3) {
        clear();
        mvprintw(0, 0, "Auteur       : COUSSON Sophie / BENESBY Quentin");
        mvprintw(1, 0, "Creation     : 01-04-2022");
        mvprintw(2, 0, "Modification : 04-04-2022");
        refresh();
        nodelay(stdscr, FALSE);
        getch();
        nodelay(stdscr, TRUE);
        clear();
        return 1;
    } else {
        return -1; /* quitter */
    }
}

int menu() {
    int touche, res;
    int pointeur, option;

    pointeur = 1;
    option = 1;
    while (1) {
        touche = getch();
        if (touche != ERR) {
            if (touche == KEY_UP) {
                if (pointeur != 1) {pointeur--;}
                else {pointeur = 4;}
            } else if (touche == KEY_DOWN) {
                if (pointeur != 4) {pointeur++;}
                else {pointeur = 1;}
            } else if (touche == '\n') {
                res = choix(pointeur, &option);
                if (res <= 0) {
                    break;
                }
            }
        }

        affiche_menu(pointeur);
        refresh();

    }
    if (res == -1) {
        return 0;
    }

    refresh();
    endwin();

    return option;
}
