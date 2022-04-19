/* position */

/*
    Auteur       : BENESBY Quentin / COUSSON Sophie
    Creation     : 29-03-2022
    Modification : 04-04-2022
*/

#ifndef __position__
#define __position__

    #include "case.h"

    typedef struct {
        unsigned long long int tableau;
    } Position;

    Position tab_cases_attaquees[64];

    int est_case_occupee(Position pos, Case c);
    int placer_dame_position(Position *pos, Case c);
    int placer_cavalier_position(Position *pos, Case c);
    int calculer_cases_attaquees(Position *pos, Case c);
    void init_cases_attaquees();
    int est_sans_attaque_mutuelle(Position pos, int version);
    int ajoute_nouvelle_dame(Position* pos, Case c);
    void supprime(Position* pos, Case c);
    int fin_partie(int nb_dames);
    void calculer_cases_attaquees_cavalier(Position* pos, Case c);
    int ajoute_nouveau_cavalier(Position* pos, Case c);
    int verification_mixte(Position dames, Position cavaliers, Case c);

#endif
