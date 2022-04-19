/*
    Auteur       : COUSSON Sophie / BENESBY Quentin
    Creation     : 08-02-2022
    Modification : 08-02-2022
*/

#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <ncurses.h>

#define TOURS_MAX 20

typedef struct {
    int marche;
    int dureeTotale;
    int avertissement;
    int dernierTour;
    int nbTours;
    int tab[TOURS_MAX];
} Chronometre;

Chronometre initialiser_chronometre() {
    Chronometre chrono;
    chrono.avertissement = 25000;
    chrono.dureeTotale = 0;
    chrono.marche = 0;
    chrono.dernierTour = 0;
    chrono.nbTours = 0;
    return chrono;
}

int intervalle_ms(struct timeval debut, struct timeval fin) {
    return (fin.tv_sec - debut.tv_sec) * 1000 + (fin.tv_usec - debut.tv_usec) / 1000;
}

int nb_ms_vers_centiemes(int nb_ms) {
    return (nb_ms/10) % 100;
}

int nb_ms_vers_secondes(int nb_ms) {
    return (nb_ms / 1000) % 60;
}

int nb_ms_vers_minutes(int nb_ms) {
    return (nb_ms / (1000 * 60)) % 60;
}

int nb_ms_vers_heures(int nb_ms) {
    return (nb_ms / (1000 * 60 * 60)) % 24;
}

void afficheTemps(int nb_ms) {
    clear();
    int s, m, h, cs;
    h = nb_ms_vers_heures(nb_ms);
    m = nb_ms_vers_minutes(nb_ms);
    s = nb_ms_vers_secondes(nb_ms);
    cs = nb_ms_vers_centiemes(nb_ms);
    printw("%2d : %2d : %2d : %2d\n", h, m, s, cs);
    refresh();
}

void afficher_duree(int y, int x, int nb_ms) {
    int s, m, h, cs;
    h = nb_ms_vers_heures(nb_ms);
    m = nb_ms_vers_minutes(nb_ms);
    s = nb_ms_vers_secondes(nb_ms);
    cs = nb_ms_vers_centiemes(nb_ms);
    mvprintw(y, x, "%2d : %2d : %2d : %2d\n", h, m, s, cs);
}

int afficheTours(Chronometre chrono) {
    if (!chrono.nbTours) {return 1;}
    int i, cmpt;
    if (LINES - 11 > 6) {
        if (!chrono.nbTours){return 6;}
        if (chrono.nbTours <= 6) {
            for (i = 1; i <= chrono.nbTours; i++) {
                mvprintw(i, COLS/2-11, "Tour %2d :", chrono.nbTours - i + 1);
                afficher_duree(i,  COLS/2-1,chrono.tab[chrono.nbTours - i]);
            }
            return chrono.nbTours;
        }
        cmpt = 1;
        for (i = chrono.nbTours; i > chrono.nbTours - 6; i--) {
            mvprintw(cmpt, COLS/2-11, "Tour %2d :", i);
            afficher_duree(cmpt, COLS/2-1 ,chrono.tab[i - 1]);
            cmpt++;
        }
        return 6;

    } else {
        int place = LINES - 13;
        if (!chrono.nbTours) {return place;}
        if (chrono.nbTours <= place) {
            for (i = 1; i <= chrono.nbTours; i++) {
                mvprintw(i, COLS/2-11, "Tour %2d :", chrono.nbTours - i + 1);
                afficher_duree(i, COLS/2-1, chrono.tab[chrono.nbTours - i]);
            }
            return place;
        }
        cmpt = 1;
        for (i = chrono.nbTours; i > chrono.nbTours - place; i--) {
            mvprintw(cmpt, COLS/2-11, "Tour %2d :", i);
            afficher_duree(cmpt, COLS/2-1, chrono.tab[i-1]);
            cmpt++;
        }
        return place;
    }
}


void ligneTraits(){
    int i = 0;
    for (; i< COLS; i++) {
        printw("-");
    }
    printw("\n");
}

void afficheOptions(){
    printw("Espace : lancer / mettre en pause\n");
    printw("r      : reinitialiser\n");
    printw("t      : marquer tour\n");
    printw("F1/F2  : incrementer / decrementer heure avertissement\n");
    printw("F3/F4  : incrementer / decrementer minute avertissement\n");
    printw("F5/F6  : incrementer / decrementer seconde avertissement\n");
    printw("q      : quitter");
}

void afficher_flash(Chronometre c, int* couleur) {
    int i = 0;

    if (c.dureeTotale % 200) {
        if (*couleur == 1) {
            *couleur = 2;
        } else {
            *couleur = 1;
        }
    }

    attron(COLOR_PAIR(*couleur));
    for (; i < 4; i++) {
        mvprintw(i, 0, "* * * * * * *");
    }
    attroff(COLOR_PAIR(*couleur));
}

void afficheAlerteTours(Chronometre chrono) {
    if (chrono.nbTours == 20) {
        init_pair(3, COLOR_RED, COLOR_RED);
        attron(COLOR_PAIR(3));
        mvprintw(0, COLS - 1, " ");
        attroff(COLOR_PAIR(3));
    }   
}

void affiche_interface(Chronometre chrono, int* couleur) {
    int pos;
    clear();
    mvprintw(0, COLS /2  - 9, "== Chronometre ==\n");
    pos = afficheTours(chrono);
    
    pos += 2;
    afficher_duree(pos, COLS/2-1, chrono.dureeTotale);
    pos++;
    mvprintw(pos, COLS/2-17, "Avertissement :");
    afficher_duree(pos, COLS / 2 -1, chrono.avertissement);
    ligneTraits();
    afficheOptions();
    afficheAlerteTours(chrono);
    if (chrono.dureeTotale > chrono.avertissement && chrono.dureeTotale < chrono.avertissement + 5000) {
        afficher_flash(chrono, couleur);
    }
    refresh();
}

void ajouteTour(Chronometre* chrono) {
    chrono->tab[chrono->nbTours] = chrono->dureeTotale;
    chrono->nbTours++;
}

void chrono() {
    struct timeval temps_debut, temps_fin;
    int touche;
    int couleur = 1;

    Chronometre chrono;
    chrono = initialiser_chronometre();


    while (1) {
        touche = getch();
        if (touche != ERR) {
            if (touche == 'q') {
                break;
            }
            if (touche == 'r') {
                chrono.dureeTotale = 0;
                chrono.marche = 0;
                chrono.dernierTour = 0;
                chrono.nbTours = 0;
            }
            if (touche == 't') {
                if (chrono.nbTours == 20) {
                    continue;
                }
                ajouteTour(&chrono);
            }
            if (touche == ' ') {
                if (!chrono.marche) {
                    gettimeofday(&temps_debut, NULL);
                    chrono.marche = 1;
                } else {
                    chrono.marche = 0;
                }
            }
            if (touche == KEY_F(1)) {
                chrono.avertissement += 3600000;
            }
            if (touche == KEY_F(2)) {
                if (chrono.avertissement > 3600000) {
                    chrono.avertissement -= 3600000;
                }
            }
            if (touche == KEY_F(3)) {
                chrono.avertissement += 60000;
            }
            if (touche == KEY_F(4)) {
                if (chrono.avertissement > 60000) {
                    chrono.avertissement -= 60000;
                }
            }
            if (touche == KEY_F(5)) {
                chrono.avertissement += 1000;
            }
            if (touche == KEY_F(6)) {
                if (chrono.avertissement > 1000) {
                    chrono.avertissement -= 1000;
                }
            }
        }

        if (chrono.marche) {
            gettimeofday(&temps_fin, NULL);
            chrono.dureeTotale += intervalle_ms(temps_debut, temps_fin);
            temps_debut = temps_fin;
        }
        affiche_interface(chrono, &couleur);
        refresh();
        usleep(7000);
    }
}


int main(void) {

    initscr();

    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLUE);
    init_pair(2, COLOR_BLUE, COLOR_GREEN);

    curs_set(FALSE);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    noecho();


    chrono();

    endwin();

    return 0;
}