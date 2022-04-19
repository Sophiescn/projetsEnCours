/* monde.h */

#ifndef __monde__
#define __monde__

    #include "serpent.h"
    #include "case.h"
    #include "pomme.h"
    #include "sauvegarde.h"

    typedef struct {
        Serpent s;
        Pommes* liste_pommes;
        Cases* liste_murs;
        int nb_pomme_mange;
    } Monde;

    int position_valide_pomme(Monde mon, Case c);
    int position_valide_serpent(Monde mon, Case cs);
    int position_valide(Monde mon, Pomme p);
    void monde_ajouter_pomme(Monde *mon, Partie partie);
    void ajouter_murs(Monde* mon);
    Monde monde_initialiser(Partie p);
    int monde_est_mort_serpent(Monde mon, Partie p);
    void suppression_pomme(Monde* mon, Pommes* supr);
    void monde_evoluer_serpent(Monde* mon, Partie p);

#endif
