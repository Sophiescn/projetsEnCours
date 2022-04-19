#include "case.h"
#include "serpent.h"
#include "pomme.h"
#include "monde.h"
#include "ncurses.h"
#include "graphique.h"
#include "sauvegarde.h"

int debut_x(Partie p) {
    return (LINES / 2 - p.hauteur / 2);
}

int debut_y(Partie p) {
    return (COLS / 2 - p.largeur / 2);
}

void interface_afficher_quadrillage(Monde mon, int nb_colonnes, int nb_lignes) {
    int center_x, center_y;
    int ligne, colonne;
    center_x = (COLS / 2) - 1;
    center_y = (LINES / 2) - 1;

    for (ligne = center_y - (nb_lignes / 2); ligne <= center_y + (nb_lignes / 2) + 1; ligne++) {
        mvprintw(ligne, center_x - (nb_colonnes / 2), "|");
        mvprintw(ligne, center_x + (nb_colonnes / 2) + 1, "|");
    }
    
    for (colonne = center_x - (nb_colonnes / 2); colonne <= center_x + (nb_colonnes / 2) + 1; colonne++) {
        mvprintw(center_y - (nb_lignes / 2), colonne, "-");
        mvprintw(center_y + (nb_lignes / 2) + 1, colonne, "-");
    }
}

void interface_afficher_pomme(Pomme pom, Partie p) {
    int center_x, center_y;
    int x, y;
    center_x = COLS / 2;
    center_y = LINES / 2;

    x = pom.c.x + center_x - (p.largeur / 2);
    y = pom.c.y + center_y - (p.hauteur / 2);

    mvprintw(y, x, "P");
}

void dessine_tete(Partie p, int x, int y) {
    int pos_x, pos_y;
    pos_x = debut_x(p) + x;
    pos_y = debut_y(p) + y;
    mvprintw(pos_x, pos_y, "o");
}

void dessine_corps(Partie p, int x, int y) {
    int pos_x, pos_y;
    pos_x = debut_x(p) + x;
    pos_y = debut_y(p) + y;
    mvprintw(pos_x, pos_y, "#");
}

void interface_afficher_serpent(Serpent ser, Partie p) {
    Cases* tete, *corps;
    tete = ser.liste_cases;
    dessine_tete(p, tete->c.y, tete->c.x);
    corps = tete->next_case;
    while(corps) {
        dessine_corps(p, corps->c.y, corps->c.x);
        corps = corps->next_case;
    }
}

void pause_espace() {
    int touche;
    while (1) {
        touche = getch();
        if (touche != ERR) {
            if (touche == ' ') {
                return;
            }
        }
    }
}

void interface_piloter(Monde* mon) {
    int touche;
    touche = getch();
    if (touche != ERR) {
        if (touche == 'z') {
            mon->s.dir = Nord;
            return;
        }
        if (touche == 'd') {
            mon->s.dir = Est;
            return;
        }
        if (touche == 's') {
            mon->s.dir = Sud;
            return;
        }
        if (touche == 'q') {
            mon->s.dir = Ouest;
            return;
        }
        if (touche == ' ') {
            nodelay(stdscr, FALSE);
            pause_espace();
            nodelay(stdscr, TRUE);
            return;
        }
    }
}


void interface_afficher_monde(Monde mon, Partie partie) {
    Pommes* pom;
    pom = mon.liste_pommes;

    clear();
    interface_afficher_quadrillage(mon, partie.largeur, partie.hauteur);
    while (pom) {
        interface_afficher_pomme(pom->p, partie);
        pom = pom->next_pomme;
    }
    interface_afficher_serpent(mon.s, partie);
    mvprintw(0, 0, "pommes mangées : %d", mon.nb_pomme_mange);
    refresh();
}
