/*
    Auteur       : BENESBY Quentin / COUSSON Sophie
    Creation     : 29-03-2022
    Modification : 04-04-2022
*/

#include "case.h"
#include "position.h"
#include "affichage.h"
#include "partie.h"
#include <ncurses.h>

void partie_dames() {
    Position pos;
    Case c;
    MEVENT ev;
    int touche;
    int nb_dames;
    int souris_x, souris_y;
    char* chaine;

    init_cases_attaquees();
    pos.tableau = 0ull;
    afficher_position(pos, 'd');
    nb_dames = 0;
    chaine = "Felicitations vous avez placer 8 dames";
    while(1) {
        touche = getch();
        if (touche == KEY_MOUSE && getmouse(&ev) == OK) {
            souris_x = ev.x;
            souris_y = ev.y; 
            if (sur_grille(souris_y, souris_x)) {
                c = coordonnees_vers_case(souris_y, souris_x);
                if (est_case_occupee(pos, c)) {
                    supprime(&pos, c);
                    nb_dames--;
                    continue;
                }
                if (ajoute_nouvelle_dame(&pos, c)) {
                    nb_dames++;
                    if (fin_partie(nb_dames)) {
                        clear();
                        nodelay(stdscr, FALSE);
                        afficher_position(pos, 'd');
                        mvprintw(0, 0, "%s", chaine);
                        refresh();
                        break;
                    }
                }
            }
        }else if (touche == 'q') {
            break;
        }
        afficher_position(pos, 'd');
        refresh();
    }
    getch();
}

void partie_cavaliers() {
    Position pos;
    Case c;
    MEVENT ev;
    int touche;
    int nb_cavaliers;
    int souris_x, souris_y;

    init_cases_attaquees();
    pos.tableau = 0ull;
    afficher_position(pos, 'c');
    nb_cavaliers = 0;
    while(1) {
        touche = getch();
        if (touche == KEY_MOUSE && getmouse(&ev) == OK) {
            souris_x = ev.x;
            souris_y = ev.y; 
            if (sur_grille(souris_y, souris_x)) {
                c = coordonnees_vers_case(souris_y, souris_x);
                if (est_case_occupee(pos, c)) {
                    supprime(&pos, c);
                    nb_cavaliers--;
                    continue;
                }
                if (ajoute_nouveau_cavalier(&pos, c)) {
                    nb_cavaliers++;
                }
            }
        }else if (touche == 'q') {
            break;
        }
        afficher_position(pos, 'c');
        refresh();
    }
    clear();
    afficher_position(pos, 'c');
    mvprintw(0, 0, "vous avez placer %d cavalier(s)", nb_cavaliers);
    refresh();
    nodelay(stdscr, FALSE);
    getch();
}

void partie_melangee() {
    Position dames, cavaliers;
    Case c;
    MEVENT ev;
    int touche;
    int nb_dames, nb_cavaliers;
    int souris_x, souris_y;
    char type;

    dames.tableau = 0ull;
    cavaliers.tableau = 0ull;
    nb_dames = 0;
    nb_cavaliers = 0;
    type = 'd';
    
    affichage_mixte(dames, cavaliers);
    while (1) {
        touche = getch();
        if (touche == KEY_MOUSE && getmouse(&ev) == OK) {
            souris_x = ev.x;
            souris_y = ev.y; 
            if (sur_grille(souris_y, souris_x)) {
                c = coordonnees_vers_case(souris_y, souris_x);
                if (est_case_occupee(dames, c)) {
                    supprime(&dames, c);
                    nb_dames--;
                    continue;
                } else if (est_case_occupee(cavaliers, c)){
                    supprime(&cavaliers, c);
                    nb_cavaliers--;
                    continue;
                }
                if (verification_mixte(dames, cavaliers, c)) {
                    if (type == 'd') {
                        if (ajoute_nouvelle_dame(&dames, c)) {
                        nb_dames++;
                        }
                    } else if (type == 'c') {
                        if (ajoute_nouveau_cavalier(&cavaliers, c)) {
                            nb_cavaliers++;
                        }
                    }
                }
            }
        } else if (touche == 'q') {
            break;
        } else if (touche == 'c' || touche == 'd') {
            type  = touche;
        }
        affichage_mixte(dames, cavaliers);
        refresh();
    }
    clear();
    affichage_mixte(dames, cavaliers);
    mvprintw(0, 0, "vous avez placer %d cavalier(s)", nb_cavaliers);
    mvprintw(1, 0, "vous avez placer %d dame(s)", nb_dames);
    refresh();
    nodelay(stdscr, FALSE);
    getch();
}
