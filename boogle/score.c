/*
    Auteur       : BENESBY Quentin / COUSSON Sophie
    Creation     : 22-03-2022
    Modification : 28-03-2022
*/

#include "score.h"
#include <stdio.h>
#include <string.h>


int score_mot(char* mot) {
    int cmpt, i;

    cmpt = 2;

    for (i = 1; i < strlen(mot) - 3; i++) {
        cmpt*=2;
    }

    return cmpt;
}

void met_a_jour_score(Partie* partie, char* mot) {
    partie->score += score_mot(mot);
}
