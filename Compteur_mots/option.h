/*
    Auteur       : BENESBY Quentin / COUSSON Sophie
    Creation     : 15-03-2022
    Modification : 21-03-2022
*/

/* option.h */

#ifndef __option__
#define __option__

    #include "transformation.h"

    #define NB_OPTIONS 2

    typedef enum {
        a, /* ordre alphabetique */
        n, /* ordre d'occurence */
        s, /* les mots suivants */
        p, /* les mots precedents */
        e, /* les expressions */
        t, /* les test */
        r /* option inexistante */
    } Option;

    typedef struct {
        Option tab[NB_OPTIONS];
        char* mot;
        int taille;
    }Options;

    Options initialise_options();
    int ordonnee_lettres(char un, char deux);
    void options_multiples(Options* o, char un, char deux);
    void identifie_options(Options* o, int argc, char* argv[]);
    Dictionnaire* ordonne_a(Dictionnaire* dico);
    Dictionnaire* ordonne_n(Dictionnaire* dico);
    Dictionnaire* ordonne_s(Mot* liste_mot, char* m);
    Dictionnaire* ordonne_p(Mot* liste_mot, char* m);

#endif
