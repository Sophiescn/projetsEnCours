#include "case.h"
#include <stdlib.h>


Case creer_case(int x, int y) {
    Case c;
    c.x = x;
    c.y = y;
    return c;
}

Cases* empile_case(Cases* liste, Case c) {
    Cases* res;
    res = (Cases*) malloc(sizeof(Case));
    if (res) {
        res->c = c;
        res->next_case = liste;
    }
    return res;
}
