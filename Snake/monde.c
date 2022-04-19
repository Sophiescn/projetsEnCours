#include "monde.h"
#include "pomme.h"
#include "serpent.h"
#include "case.h"
#include "sauvegarde.h"
#include <stdlib.h>


int position_valide_pomme(Monde mon, Case c){
    Pommes* courant;
    courant = mon.liste_pommes;
    while(courant) {
        if (courant->p.c.x == c.x && courant->p.c.y == c.y) {
            return 0;
        }
        courant = courant->next_pomme;
    }
    return 1;
}

int position_valide_serpent(Monde mon, Case cs) {
    Cases* c;
    c = mon.s.liste_cases;
    while(c) {
        if (c->c.x == cs.x && c->c.y == cs.y) {
            return 0;
        }
        c = c->next_case;
    }
    return 1;
}

int P_position_valide(Monde mon, Pomme p) {
    return position_valide_pomme(mon, p.c) && position_valide_serpent(mon, p.c);
}

int M_position_valide(Monde mon, Case c) {
    return position_valide_pomme(mon, c) && position_valide_serpent(mon, c);
}

void monde_ajouter_pomme(Monde *mon, Partie partie) {
    Pomme p;
    Pommes* po;
    p = pomme_aleatoire(partie.hauteur, partie.largeur);
    while(!P_position_valide(*mon, p)) {
        p = pomme_aleatoire(partie.hauteur, partie.largeur);
    }
    po = (Pommes*) malloc(sizeof(Pomme));
    if (!po) {
        return;
    }
    po->p = p;
    po->next_pomme = mon->liste_pommes;
    mon->liste_pommes = po;
}

Monde monde_initialiser(Partie p) {
    Monde mon;
    int i;
    mon.s = serpent_initialisation(p.hauteur, p.largeur, p.taille_serp);
    mon.liste_pommes = NULL;
    for (i = 0; i < p.nb_pommes; i++) {
        monde_ajouter_pomme(&mon, p);
    }
    mon.nb_pomme_mange = 0;
    return mon;
}

int monde_est_mort_serpent(Monde mon, Partie p) {
    Case c;
    c = serpent_case_visee(mon.s);
    if (c.x < 0 || c.x > p.largeur) {
        return 0;
    }
    if (c.y < 0 || c.y > p.hauteur) {
        return 0;
    }
    return position_valide_serpent(mon, c);
}

void suppression_pomme(Monde* mon, Pommes* supr) {
    Pommes* precedent;
    Pommes* courant;

    courant = mon->liste_pommes;
    precedent = NULL;

    while (courant->p.c.x != supr->p.c.x && courant->p.c.y != supr->p.c.y) {
        precedent = courant;
        courant = courant->next_pomme;
    }

    if (!precedent) {
        precedent = courant->next_pomme;
        free(courant);
        mon->liste_pommes = precedent;
        return;
    }
    if (courant->next_pomme) {
        precedent->next_pomme = courant->next_pomme;
    } else {
        precedent->next_pomme = NULL;
    }
    free(courant);
}

void monde_evoluer_serpent(Monde* mon, Partie p) {
    Case tmp;
    Pommes* courant_p;
    Cases* courant_c;
    int grandit;

    if (!monde_est_mort_serpent(*mon, p)) {return;}

    grandit = 0;

    courant_p = mon->liste_pommes;
    courant_c = mon->s.liste_cases;


    tmp = serpent_case_visee(mon->s);
    while (courant_p) {
        if (courant_p->p.c.x == tmp.x && courant_p->p.c.y == tmp.y) {
            grandit = 1;
            suppression_pomme(mon, courant_p);
            mon->nb_pomme_mange++;
            monde_ajouter_pomme(mon, p);
            break;
        }
        courant_p = courant_p->next_pomme;
    }

    mon->s.liste_cases = empile_case(mon->s.liste_cases, tmp);

    if (!grandit) {
        while (courant_c->next_case->next_case) {
            courant_c = courant_c->next_case;
        }

        free(courant_c->next_case);
        courant_c->next_case = NULL;
    }
}
