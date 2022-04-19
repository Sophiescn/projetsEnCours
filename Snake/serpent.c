#include "serpent.h"
#include <stdlib.h>


Serpent serpent_initialisation(int nb_lignes, int nb_colonnes, int taille) {
    Serpent serpent;
    Case c;
    int i;
    serpent.dir = Est;
    serpent.liste_cases = NULL;

    for (i = 1; i <= taille; i++) {
        c = creer_case((nb_colonnes / 2) - (taille - i), nb_lignes / 2);
        serpent.liste_cases = empile_case(serpent.liste_cases, c);
    }

    return serpent;
}

Case serpent_case_visee(Serpent serp) {
    Case tmp;
    tmp = serp.liste_cases->c;
    if (serp.dir == Nord) {
        tmp.y--;
    } else if (serp.dir == Est) {
        tmp.x++;
    } else if (serp.dir == Sud) {
        tmp.y++;
    } else if (serp.dir == Ouest) {
        tmp.x--;
    }
    return tmp;
}
