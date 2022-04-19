/*
    Auteur       : BENESBY Quentin / COUSSON Sophie
    Creation     : 15-03-2022
    Modification : 21-03-2022
*/

#include "option.h"
#include "transformation.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


Options initialise_options(){
    Options o;
    o.tab[0] = r;
    o.tab[1] = r;
    o.mot = "\0";
    o.taille = 1;
    return o;
}

int ordonnee_lettres(char un, char deux) {
    return un < deux;
}

void options_multiples(Options* o, char un, char deux) {
    if (un == 'a' && deux == 'e') {
        o->tab[0] = a;
        o->tab[1] = e;
    }else if (un == 'a' && deux == 's') {
        o->tab[0] = a;
        o->tab[1] = s;
    } else if (un == 'a' && deux == 'p') {
        o->tab[0] = a;
        o->tab[1] = p;
    } else if (un == 'e' && deux == 'n') {
        o->tab[0] = e;
        o->tab[1] = n;
    } else if (un == 'n' && deux == 's') {
        o->tab[0] = n;
        o->tab[1] = s;
    } else if (un == 'n' && deux == 'p') {
        o->tab[0] = n;
        o->tab[1] = p;
    }
}

void identifie_options(Options* o, int argc, char* argv[]) {
    char un, deux, trois;
    int i;
    if (argc != 3 && argc != 5) {
        if (argc == 4){
            if (argv[2][1] == 'e'){
                o->tab[0] = e;
                o->taille = atoi(argv[3]);
            } else if (argv[2][1] == 's'){
                o->tab[0] = s;
                o->mot = argv[3];
            } else if (argv[2][1] == 'p'){
                o->tab[0] = p;
                o->mot = argv[3];
            }
        }
    }
    if (argc == 3) {
        if (argv[2][1] == 'a'){
            o->tab[0] = a;
        } else if (argv[2][1] == 'n') {
            o->tab[0] = n;
        }
    } else if (argc == 2) {
        if (!strcmp(argv[1], "-test")) {
            o->tab[0] = t;
        }
    } else {
        un = 'v'; /* vide*/
        deux = 'v'; /* vide */
        for(i = 2; i < argc; i++) {
            if (argv[i][0] == '-') {
                if (un == 'v') {
                    un = argv[i][1];
                }else if (deux == 'v') {
                    deux = argv[i][1];
                } else {
                    return;
                }
            } else {
                if (un == 'e' || deux == e) {
                    o->taille = atoi(argv[i]);
                } else {
                    o->mot = argv[i];
                }
            }
        }
        if (!ordonnee_lettres(un, deux)) {
            trois = un;
            un = deux;
            deux = trois;
        }
        options_multiples(o, un, deux);
    }
}

Dictionnaire* ordonne_a(Dictionnaire* dico) {
    Dictionnaire* courant, *temp, *tete, *precedent;
    int res;
    if (!dico) {
        return dico;
    }
    courant = dico;
    precedent = courant;
    tete = dico;
    /* on parcourt le dictionaire */
    while (courant) {
        if (courant->mot_suivant) {
            res = strcmp(courant->m, courant->mot_suivant->m);
            if (res > 0) {
                temp = courant->mot_suivant->mot_suivant;
                if (courant == tete) {
                    tete = courant->mot_suivant;
                } else {
                    precedent->mot_suivant = courant->mot_suivant;
                }
                
                courant->mot_suivant->mot_suivant = courant;
                courant->mot_suivant = temp; 
                precedent = courant;
                courant = tete;
            } else {
                precedent = courant;
                courant = courant->mot_suivant;
            }
        } else {
            break;
        }
    }
    return tete;
}

Dictionnaire* ordonne_n(Dictionnaire* dico) {
   Dictionnaire* courant, *temp, *tete, *precedent;
    if (!dico) {
        return dico;
    }
    courant = dico;
    precedent = courant;
    tete = dico;

    /* on parcourt le dictionaire */
    while (courant) {
        if (courant->mot_suivant) {
            if (courant->nb_occurences <= courant->mot_suivant->nb_occurences) {
                if (courant->nb_occurences == courant->mot_suivant->nb_occurences && strcmp(courant->m, courant->mot_suivant->m) < 0) {
                    precedent = courant;
                    courant = courant->mot_suivant;
                } else {
                    temp = courant->mot_suivant->mot_suivant;
                    if (courant == tete) {
                        tete = courant->mot_suivant;
                    } else {
                        precedent->mot_suivant = courant->mot_suivant;
                    }
                    
                    courant->mot_suivant->mot_suivant = courant;
                    courant->mot_suivant = temp; 
                    precedent = courant;
                    courant = tete;
                }
            } else {
                precedent = courant;
                courant = courant->mot_suivant;
            }
        } else {
            break;
        }
    }
    return tete; 
}

Dictionnaire* ordonne_s(Mot* liste_mot, char* m) {
    Dictionnaire* dico;
    Mot* nouvelle;
    Mot* mot;
    mot = liste_mot;
    nouvelle = NULL;

    while (mot) {
        if (!strcmp(mot->m, m)) {
            if (mot->mot_suivant) {
                nouvelle = empilement_cellule(nouvelle, mot->mot_suivant->m);
            } else {
                break;
            }
        }
        mot = mot->mot_suivant;
    }
    dico = NULL;
    dico = mot_a_dictionnaire_1(dico, nouvelle);
    return dico;
}

Dictionnaire* ordonne_p(Mot* liste_mot, char* m) {
    Dictionnaire* dico;
    Mot* nouvelle;
    Mot* mot;
    mot = liste_mot;
    nouvelle = NULL;

    while (mot) {
        if (!strcmp(mot->m, m)) {
            if (mot->mot_precedent) {
                nouvelle = empilement_cellule(nouvelle, mot->mot_precedent->m);
            }
        }
        mot = mot->mot_suivant;
    }
    dico = NULL;
    dico = mot_a_dictionnaire_1(dico, nouvelle);
    return dico;
}
