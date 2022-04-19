/* pomme.h */

#ifndef __pomme__
#define __pomme__

    #include "case.h"

    typedef struct {
        Case c;
    } Pomme;

    typedef struct pommes {
        Pomme p;
        struct pommes* next_pomme;
    } Pommes;

    Case case_aleatoire(int nb_lignes, int nb_colonnes);
    Pomme pomme_aleatoire(int nb_lignes, int nb_colonnes);

#endif
