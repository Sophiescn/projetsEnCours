#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "pomme.h"
#include "case.h"

Case case_aleatoire(int nb_lignes, int nb_colonnes) {
    Case c;
    c = creer_case(rand() % nb_colonnes, rand() % nb_lignes);
    return c;
}

Pomme pomme_aleatoire(int nb_lignes, int nb_colonnes) {
    Pomme p;
    p.c = case_aleatoire(nb_lignes, nb_colonnes);
    return p;
}


