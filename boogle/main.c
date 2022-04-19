/*
    Auteur       : BENESBY Quentin / COUSSON Sophie
    Creation     : 22-03-2022
    Modification : 28-03-2022
*/

#include "grille.h"
#include "score.h"
#include "partie.h"
#include "fin_jeu.h"
#include "ouverture.h"
#include "affichage.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>


int main(void) {
    Partie p;
    Mot* trouve;
    char** dictionnaire;
    Position* positions;
    int taille;
    int touche;
    int valide;
    int souris_x, souris_y;
    int pos_x, pos_y;
    char* mot;
    int pos;
    char c;
    MEVENT ev;

    /* random */
    srand(time(NULL));

    dictionnaire = (char**) malloc(sizeof(char*) * 400000);
    
    /* taille du fichier dictionnaire ouvert */
    taille = lecture_fichier("mot", dictionnaire);
    
    p = initialise_partie(dictionnaire, taille);
    trouve = NULL;
    positions = NULL;

    /* mot en attente */
    mot = (char*) malloc(sizeof(char) * 32);

    pos = 0;

    /* boucle principale */
    initscr();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
    curs_set(FALSE);

    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);
    init_pair(3, COLOR_MAGENTA, COLOR_BLACK);

    pos_x = (COLS / 2) - (TAILLE_GRILLE / 2) + 1;
    pos_y = (LINES / 2) - (TAILLE_GRILLE / 2);

    while (1) {
        touche = getch();
        if (touche == KEY_MOUSE && getmouse(&ev) == OK) {
            souris_x = ev.x;
            souris_y = ev.y;

            if (sur_grille(pos_x, pos_y, souris_x, souris_y)) {
                /* sur quel caractere le joueur a appuye */
                if (positions) {
                    valide = lettre_valide(*positions, souris_x, souris_y, 3);
                    /* position invalide */
                    if (!valide){continue;}
                    /* position actuel (pas deux fois le meme caractere) */
                    if (valide == 2) {
                        positions = positions->precedent;
                        souris_x -= pos_x;
                        souris_x /= 3;
                        souris_y -= pos_y;
                        change_etat(&p.grille, souris_x, souris_y, 0);
                        mot[pos - 1] = '\0';
                        pos --;
                        affiche(p);
                        continue;
                    }
                }
                if (ajoute_position(&positions, souris_x, souris_y)) {
                    souris_x -= pos_x;
                    souris_x /= 3;
                    souris_y -= pos_y;

                    c = change_etat(&p.grille, souris_x, souris_y, 1);
                    mot[pos] = c + 32;

                    mvprintw(10, pos, "%c", c);
                    pos++;
                }
            }
        /* en cas de touche espace arret de saisie du mot */
        } else if (touche == ' ') {
            mot[pos] = '\0';
            pos = 0;
            /* mot dans le dictionnaire */
            if (recherche(dictionnaire, mot, taille)) {
                /* mot pas deja utilise */
                if (!trouve || !est_dans_trouve(trouve, mot)) {
                    insere_tete_trouve(&trouve, mot);
                    met_a_jour_score(&p, mot);
            /* dans les autres cas on perd un essais et condition de fin */
                } else {
                    p.essais--;
                    if (verifie_essais(p)) {
                        clear();
                        nodelay(stdscr, FALSE);
                        break;
                    }
                }
            } else {
                p.essais--;
                if (verifie_essais(p)) {
                    clear();
                    nodelay(stdscr, FALSE);
                    break;
                }
            }
            /* on recommence apres la saisie d'un mot */
            reinitialiser_etat(&p.grille);
            positions = NULL;
            clear();
            mot = (char*) malloc(sizeof(char) * 32);
        /* on quitte */
        } else if (touche == 'q') {
            break;
        }
        affiche_liste(trouve);  /* faccultatif actuellement juste pour test */
        affiche(p);
    }

    /* affichage score */

    mvprintw(0, 0, "score : %d", p.score);

    refresh();

    getch();
    endwin();


    return 0;
}


/*


fonction qui modifie les etats
-
recupere un mot


boucle principale







*/
