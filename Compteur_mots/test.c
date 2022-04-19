/*
    Auteur       : BENESBY Quentin / COUSSON Sophie
    Creation     : 15-03-2022
    Modification : 21-03-2022
*/

#include "test.h"
#include "option.h"
#include "ouverture.h"
#include "transformation.h"
#include <string.h>
#include <stdio.h>


int test_cherche_incremente() {
    Dictionnaire* dico = NULL;
    Mot un, deux, trois;

    un.m = "a";
    deux.m = "ab";
    trois.m = "abc";
    un.mot_precedent = NULL;
    un.mot_suivant = &deux;
    deux.mot_precedent = &un;
    deux.mot_suivant = &trois;
    trois.mot_precedent = &deux;
    trois.mot_suivant = NULL;

    dico = mot_a_dictionnaire_1(dico, &un);


    if (!cherche_incremente("abc", dico)) {
        printf("ERREUR test 1\n");
        return 0;
    }

    if (!cherche_incremente("a", dico)) {
        printf("ERREUR test 2\n");
        return 0;
    }

    if (cherche_incremente("abcde", dico)) {
        printf("ERREUR test 3\n");
        return 0;
    }

    if (cherche_incremente("dico", dico)) {
        printf("ERREUR test 4\n");
        return 0;
    }

    return 1;
}

int test_longueur() {
    Dictionnaire* dico = NULL;
    Mot un, deux, trois;

    un.m = "a";
    deux.m = "ab";
    trois.m = "abc";
    un.mot_precedent = NULL;
    un.mot_suivant = &deux;
    deux.mot_precedent = &un;
    deux.mot_suivant = &trois;
    trois.mot_precedent = &deux;
    trois.mot_suivant = NULL;

    dico = mot_a_dictionnaire_1(dico, &un);

    if (longueur(*dico) != 3) {
        printf("ERREUR test 1\n");
        return 0;
    }

    if (longueur(*dico) < 3) {
        printf("ERREUR test 2\n");
        return 0;
    }

    if (longueur(*dico) != strlen("abc")) {
        printf("ERREUR test 3\n");
        return 0;
    }
    return 1;
}

int test_ordonnee_lettres() {
    char c1 = 'a';
    char c2 = 'z';
    char c3 = '1';
    char c4 = '9';

    if (!ordonnee_lettres(c1, c2)) {
        printf("ERREUR test 1\n");
        return 0;
    }

    if (ordonnee_lettres(c2, c1)) {
        printf("ERREUR test 2\n");
        return 0;
    }

    if (!ordonnee_lettres(c3, c4)) {
        printf("ERREUR test 3\n");
        return 0;
    }

    return 1;
}

int test_taille_fichier() {
    FILE* f = fopen("makefile", "r"); /* nombre de caractere dans le fichier makefile = 581 */

    if (taille_fichier(f) != 581) {
        printf("ERREUR test 1\n");
        return 0;
    }

    if (taille_fichier(f) == -8) {
        printf("ERREUR test 2\n");
        return 0;
    }

    fclose(f);

    return 1;
}

int test_mot_valide() {
    char* mot1 = "motvalide";
    char* mot2 = "MotNonValide";
    char* mot3 = "m0tn0nvalide";
    char* mot4 = "M0TN0NVALIDE";

    if (!mot_valide(mot1)) {
        printf("ERREUR test 1\n");
        return 0;
    }

    if (mot_valide(mot2)) {
        printf("ERREUR test 2\n");
        return 0;
    }

    if (mot_valide(mot3)) {
        printf("ERREUR test 3\n");
        return 0;
    }

    if (mot_valide(mot4)) {
        printf("ERREUR test 4\n");
        return 0;
    }

    return 1;
}

int test_ordonne_a() {
    Dictionnaire* dico_test = NULL;
    Dictionnaire* dico_comp = NULL;

    Dictionnaire* actuel_test,* actuel;
    Mot un_test, deux_test, trois_test;
    Mot un, deux, trois;

    un_test.m = "a";
    deux_test.m = "ab";
    trois_test.m = "abc";
    un.m = "abc";
    deux.m = "ab";
    trois.m = "a";

    un_test.mot_precedent = NULL;
    un_test.mot_suivant = &deux_test;
    deux_test.mot_precedent = &un_test;
    deux_test.mot_suivant = &trois_test;
    trois_test.mot_precedent = &deux_test;
    trois_test.mot_suivant = NULL;

    un.mot_precedent = NULL;
    un.mot_suivant = &deux;
    deux.mot_precedent = &un;
    deux.mot_suivant = &trois;
    trois.mot_precedent = &deux;
    trois.mot_suivant = NULL;

    /* dico non trie */
    dico_test = mot_a_dictionnaire_1(dico_test, &un_test);
    /* dico trie */
    dico_comp = mot_a_dictionnaire_1(dico_comp, &un);

    /* fonction test */
    dico_test = ordonne_a(dico_test);

    actuel_test = dico_test;
    actuel = dico_comp;

    /* comparaison des deux dictionnaires */
    while (actuel) {
        if (strcmp(actuel->m, actuel_test->m)) {
            printf("ERREUR test 1\n");
            return 0;
        }
        actuel = actuel->mot_suivant;
        actuel_test = actuel_test->mot_suivant;
    }

    return 1;
}

int test_ordonne_n() {
    Dictionnaire* dico_test = NULL;
    Dictionnaire* dico_comp = NULL;

    Dictionnaire* actuel_test,* actuel;
    Mot un_test, deux_test, trois_test;
    Mot un, deux, trois;

    un_test.m = "a";
    deux_test.m = "ab";
    trois_test.m = "a";
    un.m = "ab";
    deux.m = "a";
    trois.m = "a";

    un_test.mot_precedent = NULL;
    un_test.mot_suivant = &deux_test;
    deux_test.mot_precedent = &un_test;
    deux_test.mot_suivant = &trois_test;
    trois_test.mot_precedent = &deux_test;
    trois_test.mot_suivant = NULL;

    un.mot_precedent = NULL;
    un.mot_suivant = &deux;
    deux.mot_precedent = &un;
    deux.mot_suivant = &trois;
    trois.mot_precedent = &deux;
    trois.mot_suivant = NULL;

    /* dico non trie */
    dico_test = mot_a_dictionnaire_1(dico_test, &un_test);
    /* dico trie */
    dico_comp = mot_a_dictionnaire_1(dico_comp, &un);

    /* fonction test */
    dico_test = ordonne_n(dico_test);

    actuel_test = dico_test;
    actuel = dico_comp;

    /* comparaison des deux dictionnaires */
    while (actuel) {
        if (strcmp(actuel->m, actuel_test->m)) {
            printf("ERREUR test 1\n");
            return 0;
        }
        actuel = actuel->mot_suivant;
        actuel_test = actuel_test->mot_suivant;
    }

    return 1;
}

int test_ordonne_s() {
    Dictionnaire* dico_test = NULL;
    Dictionnaire* dico_comp = NULL;

    Dictionnaire* actuel_test,* actuel;
    Mot un_test, deux_test, trois_test;
    Mot un;

    un_test.m = "a";
    deux_test.m = "b";
    trois_test.m = "c";
    un.m = "c";

    un_test.mot_precedent = NULL;
    un_test.mot_suivant = &deux_test;
    deux_test.mot_precedent = &un_test;
    deux_test.mot_suivant = &trois_test;
    trois_test.mot_precedent = &deux_test;
    trois_test.mot_suivant = NULL;

    un.mot_precedent = NULL;
    un.mot_suivant = NULL;

    /* dico trie */
    dico_comp = mot_a_dictionnaire_1(dico_comp, &un);

    /* fonction test */
    dico_test = ordonne_s(&un_test, "b");

    actuel_test = dico_test;
    actuel = dico_comp;

    /* comparaison des deux dictionnaires */
    while (actuel) {
        if (strcmp(actuel->m, actuel_test->m)) {
            printf("ERREUR test 1\n");
            return 0;
        }
        actuel = actuel->mot_suivant;
        actuel_test = actuel_test->mot_suivant;
    }

    return 1;
}

int test_ordonne_p() {
    Dictionnaire* dico_test = NULL;
    Dictionnaire* dico_comp = NULL;

    Dictionnaire* actuel_test,* actuel;
    Mot un_test, deux_test, trois_test;
    Mot un;

    un_test.m = "a";
    deux_test.m = "b";
    trois_test.m = "c";
    un.m = "a";

    un_test.mot_precedent = NULL;
    un_test.mot_suivant = &deux_test;
    deux_test.mot_precedent = &un_test;
    deux_test.mot_suivant = &trois_test;
    trois_test.mot_precedent = &deux_test;
    trois_test.mot_suivant = NULL;

    un.mot_precedent = NULL;
    un.mot_suivant = NULL;

    /* dico trie */
    dico_comp = mot_a_dictionnaire_1(dico_comp, &un);

    /* fonction test */
    dico_test = ordonne_p(&un_test, "b");

    actuel_test = dico_test;
    actuel = dico_comp;

    /* comparaison des deux dictionnaires */
    while (actuel) {
        if (strcmp(actuel->m, actuel_test->m)) {
            printf("ERREUR test 1\n");
            return 0;
        }
        actuel = actuel->mot_suivant;
        actuel_test = actuel_test->mot_suivant;
    }

    return 1;
}

int test_test() {
    if (!test_cherche_incremente()) {
        printf("test_cherche_incremente()\n");
        return 0;
    }

    if (!test_longueur()) {
        printf("test_longueur()\n");
        return 0;
    }

    if (!test_ordonnee_lettres()) {
        printf("test_ordonnee_lettres()\n");
        return 0;
    }

    if (!test_taille_fichier()) {
        printf("test_taille_fichier()\n");
        return 0;
    }

    if (!test_mot_valide()) {
        printf("test_mot_valide()\n");
        return 0;
    }
    if (!test_ordonne_a()) {
        printf("test_ordonne_a()\n");
        return 0;
    }

    if (!test_ordonne_n()) {
        printf("test_ordonne_n()\n");
        return 0;
    }

    if (!test_ordonne_s()) {
        printf("test_ordonne_s()\n");
        return 0;
    }

    if (!test_ordonne_p()) {
        printf("test_ordonne_p()\n");
        return 0;
    }

    return 1;
}
