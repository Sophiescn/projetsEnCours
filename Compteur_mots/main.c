/*
    Auteur       : BENESBY Quentin / COUSSON Sophie
    Creation     : 15-03-2022
    Modification : 21-03-2022
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ouverture.h"
#include "transformation.h"
#include "option.h"
#include "test.h"

int main(int argc, char* argv[]) {
    Options op;
    char* chaine;
    Mot* liste;
    Dictionnaire* d;

    op = initialise_options();
    identifie_options(&op, argc, argv);

    if (op.tab[0] == r) {return 0;}

    if (op.tab[0] == t) {
        if (test_test()) {
            printf("Aucun probleme detectes\n");
        }
        return 0;
    }

    chaine = lecture_fichier(argv[1]);
    if (!chaine) {
        return 0;
    }
    liste = ajoute_liste(chaine);
    d = NULL;
    if ((op.tab[0] == a && op.tab[1] == r) || (op.tab[0] == n && op.tab[1] == r)) {    
        d = mot_a_dictionnaire_1(d, liste);
        if (op.tab[0] == a) {
            d = ordonne_a(d);
        } else {
            d = ordonne_n(d);
        }
        affichage_dico(d);
        return 0;
    } 
    liste = renverse_liste(liste);
    if (op.tab[0] == s || op.tab[1] == s) {
        d = ordonne_s(liste, op.mot);
    } else if (op.tab[0] == p || op.tab[1] == p) {
        d = ordonne_p(liste, op.mot);
    } else if (op.tab[0] == e || op.tab[1] == e) {
        /* d = ordonne_e(liste, op.taille); */
        return 0;
    }
    if (op.tab[0] == a) {
        d = ordonne_a(d);
    } else if (op.tab[0] == n) {
        d = ordonne_n(d);
    }
    
    affichage_dico(d);
    
    return 0;
}
