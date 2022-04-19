/*
    Auteur       : BENESBY Quentin / COUSSON Sophie
    Creation     : 29-03-2022
    Modification : 04-04-2022
*/

#include "menu.h"
#include "partie.h"
#include <ncurses.h>

int main() {
    int option;

    initscr();
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);

    option = menu();
    clear();
    if (option == 1) {
        partie_dames();
    } else if (option == 2) {
        partie_cavaliers();
    } else if (option == 3) {
        partie_melangee();
    }
    endwin();
    return 0;
}
