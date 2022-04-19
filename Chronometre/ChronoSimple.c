/*
    Auteur       : COUSSON Sophie / BENESBY Quentin
    Creation     : 08-02-2022
    Modification : 08-02-2022
*/

#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <ncurses.h>


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
    mvprintw(LINES-1, COLS/2-9, "%2d : %2d : %2d : %2d\n", h, m, s, cs);
    refresh();
}

int chronometre() {
    
    struct timeval temps_debut, temps_fin;
    int sec;

    gettimeofday(&temps_debut, NULL);

    while (1) {
        gettimeofday(&temps_fin, NULL);
        afficheTemps(intervalle_ms(temps_debut, temps_fin));
        usleep(500000);
    }
}


int main(void) {

    initscr();
    curs_set(FALSE);

    chronometre();

    refresh();
    getch();
    endwin();

    return 0;
}