#include "case.h"
#include "serpent.h"
#include "pomme.h"
#include "graphique.h"
#include "monde.h"
#include "sauvegarde.h"

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>


int main(void) {

    Monde mon;
    Partie p;

    lis_fichier(&p);

    srand(time(NULL));

    initscr();

    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLUE);
    init_pair(2, COLOR_BLUE, COLOR_GREEN);

    curs_set(FALSE);
    keypad(stdscr, TRUE);
    noecho();


    mon = monde_initialiser(p);
    interface_afficher_monde(mon, p);
    getch();
    nodelay(stdscr, TRUE);
    while (monde_est_mort_serpent(mon, p)) {
        monde_evoluer_serpent(&mon, p);
        interface_afficher_monde(mon, p);
        usleep(p.raffraichissement);
        interface_piloter(&mon);
    }


    getch();
    endwin();
    return 0;
}
