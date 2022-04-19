/*
    Auteur       : BENESBY Quentin / COUSSON Sophie
    Creation     : 22-03-2022
    Modification : 28-03-2022
*/

#include "partie.h"
#include "grille.h"
#include "score.h"
#include "affichage.h"
#include <ncurses.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>


Partie initialise_partie(char** dictionnaire, int taille) {
    Grille grille;
    Partie partie;

    remplir_grille(&grille);

    partie.grille = grille;
    partie.score = 0;
    partie.dictionnaire = dictionnaire;
    partie.taille_dictionnaire = taille;
    partie.essais = 4; 

    return partie;
}

int sur_grille(int dim_x, int dim_y, int pos_x, int pos_y) {
    return dim_x <= pos_x && pos_x <= dim_x + 11 && dim_y <= pos_y && pos_y <= dim_y + 3;
}

int lettre_valide(Position p, int pos_x, int pos_y, int taille_case) {
    if (p.x == pos_x - taille_case || p.x == pos_x + taille_case) {
        if (p.y == pos_y - 1) {return 1;}
        if (p.y == pos_y) {return 1;}
        if (p.y == pos_y + 1) {return 1;}
    } else if (p.x == pos_x) {
        if (p.y == pos_y - 1) {return 1;}
        if (p.y == pos_y + 1) {return 1;}
        if (p.y == pos_y) {return 2;}
    }
    return 0;
}

void selection_mots(Grille g, int pos_x, int pos_y) {
    /*
    int touche, pos;
    int souris_x, souris_y;
    int precedent_x, precedent_y;
    char lettre;
    char* mot;
    MEVENT ev;
    pos = 0;
    precedent_x = 0;
    precedent_y = 0;
    
    while (1) {
        touche = getch();
        if (touche == KEY_MOUSE && getmouse(&ev) == OK) {
            souris_x = ev.x;
            souris_y = ev.y;

            if (sur_grille(pos_x, pos_y, souris_x, souris_y)) {
                if (!precedent_x && !precedent_y) {
                    souris_x -= pos_x;
                    souris_x /= 3;
                    souris_y -= pos_y;
                }
                

                lettre = change_etat(&g, souris_x, souris_y);
                mot[pos] = lettre;

                mvprintw(10, pos, "%c", lettre);
                pos++;

                mvprintw(0, 0, "%d %d", souris_x, souris_y);
            }
        } else if (touche == ' ') {
            mot[pos] = '\0';
            pos = 0;
            mvprintw(13, 0, "%s", mot);
        }

        affichage_grille(g);
        affichage_aide();
        affichage_score(1000);
        refresh();
    }
    */
}

Mot* initialise_trouve(char* mot) {
    Mot* m;

    m = (Mot*) malloc(sizeof(Mot));
    assert(m);

    m->m = mot;
    m->suivant = NULL;
    return m;
}

void insere_tete_trouve(Trouve* L, char* mot) {
    Mot* m;

    m = initialise_trouve(mot);
    assert(m);
    m->suivant = *L;
    *L = m;
}

int est_dans_trouve(Trouve L, char* mot) {
    Mot* courant;

    if (!L) {
        return 0;
    }

    courant = L;
    while (courant) {
        if (!strcmp(courant->m, mot)) {
            return 1;
        }
        courant = courant->suivant;
    }
    return 0;
}

void affiche_liste(Trouve L) {
    Mot* courant;

    if (!L) {return;}

    courant = L;
    move(15, 0);
    while (courant) {
        printw("%s ", courant->m);
        courant = courant->suivant;
    }
}

Position* alloue_place(int x, int y) {
    Position* p;
    p = (Position*) malloc(sizeof(Position));
    assert(p);
    p->x = x;
    p->y = y;
    p->precedent = NULL;
    return p;
}

int position_vide(Position* p, int x, int y) {
    Position* temp;
    temp = p;
    while(temp) {
        if (temp->x == x && temp->y == y) {
            return 0;
        }
        temp = temp->precedent;
    }
    return 1;
}

int ajoute_position(Position** p, int x, int y) {
    Position* temp;
    if (position_vide(*p, x, y)) {
        temp = alloue_place(x, y);
        temp->precedent = *p;
        *p = temp;
        return 1;
    }
    return 0;
}
