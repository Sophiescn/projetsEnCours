/* serpent.h */

#ifndef __serpent__
#define __serpent__

    #include "case.h"


    typedef struct serpent {
        Direction dir;
        Cases* liste_cases;
    } Serpent;

    Serpent serpent_initialisation(int nb_lignes, int nb_colonnes, int taille);
    Case serpent_case_visee(Serpent serp);

#endif
