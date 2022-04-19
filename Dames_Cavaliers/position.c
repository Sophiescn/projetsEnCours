/*
    Auteur       : BENESBY Quentin / COUSSON Sophie
    Creation     : 29-03-2022
    Modification : 04-04-2022
*/

#include "position.h"
#include "case.h"
#include "affichage.h"

int est_case_occupee(Position pos, Case c) {
    return (pos.tableau >> c) & 1;
}

int placer_dame_position(Position *pos, Case c) {
    if (est_case_occupee(*pos, c)){
        return 0;
    }

    pos->tableau = (pos->tableau | (1ull << c));
    return 1;
}

int placer_cavalier_position(Position *pos, Case c) {
    if (est_case_occupee(*pos, c)){
        return 0;
    }

    pos->tableau = (pos->tableau | (1ull << c));
    return 1;
}

int calculer_cases_attaquees(Position* pos, Case c) {
    int i;
    int position;
    int bord_d, bord_g;
    position = c;
    bord_d = 0;
    bord_g = 0;

    /* verticale */
    for(i = c % 8; i < 64; i += 8) {
        if (i != c) {
            placer_dame_position(pos, i);
        }
    }

    /* l'horizontale */
    for (i = c - (c % 8); i <= c - (c % 8) + 7; i++) {
        if (i != c) {
            placer_dame_position(pos, i);
        }
    }

    /* les diagonales en dessous de c */
    for (i = 1; i <= (c / 8); i++) {
        position -= 8;
        /* on a atteind un bord a droite ou c est contre un bord a droite */
        if (c % 8 != 7 && !bord_d) {
            if (c != position + i && position + i >= 0 && position + i <= 63) {
                placer_dame_position(pos, position + i);
                /* si on a atteind un bord alors plus de diagobale */
                if ((position + i) % 8 == 7){bord_d = 1;}
            }
        }
        /* on a atteind un bord a gauche ou c est contre un bord a gauche */
        if (c % 8 != 0 && !bord_g) {
            if (c != position - i && position - i >= 0 && position - i <= 63) {
                placer_dame_position(pos, position - i);
                /* si on a atteind un bord alors plus de diagobale */
                if ((position - i) % 8 == 0) {bord_g = 1;}
            }
        }
    }

    position = c;
    bord_g = 0;
    bord_d = 0;
    if (c != 63) {
        for (i = 1; i < 64; i++) {
            position += 8;
            /* on a atteind un bord a gauche ou c est contre un bord a gauche */
            if (c % 8 != 0 && !bord_g) {
                if (c != position - i && position - i >= 0 && position - i <= 63) {
                    placer_dame_position(pos, position - i);
                    /* si on a atteind un bord alors plus de diagobale */
                    if ((position - i) % 8 == 0) {bord_g = 1;}
                } 
            }/* on a atteind un bord a droite ou c est contre un bord a droite */
            if (c%8 != 7 && !bord_d) {
                if (c != position + i && position + i >= 0 && position + i <= 63) {
                    placer_dame_position(pos, position + i);
                    /* si on a atteind un bord alors plus de diagobale */
                    if ((position + i) % 8 == 7) {bord_d = 1;}
                }
            }
        } 
    }
    return 1;
}

void calculer_cases_attaquees_cavalier(Position* pos, Case c) {
    int sup, inf, droite, gauche;

    if (c / 8 == 7) {
        sup = 0;
    } else if ((c + 8) / 8 == 7) {
        sup = 1;
    } else{
        sup = 2;
    }

    if (c % 8 == 0) {
        gauche = 0;
    } else if ((c - 1) % 8 == 0) {
        gauche = 1;
    } else {
        gauche = 2;
    }

    if (c % 8 == 7) {
        droite = 0;
    } else if ((c + 1) % 8 == 7) {
        droite = 1;
    } else {
        droite = 2;
    }

    if (c / 8 == 0) {
        inf = 0;
    } else if ((c - 8) / 8 == 0) {
        inf = 1;
    } else {
        inf = 2;
    }
    
    if (sup) {
        if (gauche == 2) {
            placer_cavalier_position(pos, c + 8 - 2);
        }
        if (droite == 2) {
            placer_cavalier_position(pos, c + 8 + 2);
        }
    }
    if (sup == 2) {
        if (gauche) {
            placer_cavalier_position(pos, c + 2 * 8 - 1);
        }
        if (droite) {
            placer_cavalier_position(pos, c + 2 * 8 + 1);
        }
    }

    if (inf) {
        if (gauche == 2) {
            placer_cavalier_position(pos, c - 8 - 2);
        }
        if (droite == 2) {
            placer_cavalier_position(pos, c - 8 + 2);
        }
    }

    if (inf == 2) {
        if (gauche) {
            placer_cavalier_position(pos, c - 2 * 8 - 1);
        }
        if (droite) {
            placer_cavalier_position(pos, c - 2 * 8 + 1);
        }
    }
}

void init_cases_attaquees() {
    int i;
    for(i = 0; i < 64; i++) {
        calculer_cases_attaquees(&tab_cases_attaquees[i], i);
    }
}

int est_sans_attaque_mutuelle(Position pos, int version) {
    Position attaquees;
    int i;
    attaquees.tableau = 0ull;
    for (i = 0; i < 64; i++) {
        if ((pos.tableau >> i) & 1) {
            if (version == 1) {
                calculer_cases_attaquees(&attaquees, i);
            } else {
                calculer_cases_attaquees_cavalier(&attaquees, i);
            }
        }
    }

    for (i = 0; i < 64; i++) {
        if ((pos.tableau >> i) & (attaquees.tableau >> i)) {
            return 0;
        }
    }
    return 1;
}

int ajoute_nouvelle_dame(Position* pos, Case c) {
    Position temp;
    int res;
    temp.tableau = 0ull;
    temp.tableau = pos->tableau;
    placer_dame_position(&temp, c);
    res = est_sans_attaque_mutuelle(temp, 1);

    if (res) {
        placer_dame_position(pos, c);
        return 1;
    }
    return 0;
}

void supprime(Position* pos, Case c) {
    pos->tableau = pos->tableau & ~(1ull << c);
}

int fin_partie(int nb_dames) {
    return nb_dames == 8;
}

int ajoute_nouveau_cavalier(Position* pos, Case c) {
    Position temp;
    int res;
    temp.tableau = 0ull;
    temp.tableau = pos->tableau;
    placer_cavalier_position(&temp, c);
    res = est_sans_attaque_mutuelle(temp, 2);

    if (res) {
        placer_cavalier_position(pos, c);
        return 1;
    }
    return 0;
}

int verification_mixte(Position dames, Position cavaliers, Case c) {
    Position temp_d, temp_c;
    int res1, res2;
    temp_d.tableau = 0ull;
    temp_c.tableau = 0ull;
    temp_d.tableau = dames.tableau;
    temp_c.tableau = cavaliers.tableau;
    placer_dame_position(&temp_d, c);
    placer_cavalier_position(&temp_c, c);
    res1 = est_sans_attaque_mutuelle(temp_d, 1);
    res2 = est_sans_attaque_mutuelle(temp_c, 2);
    return res1 && res2;
}

