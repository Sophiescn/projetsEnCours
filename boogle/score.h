/*
    Auteur       : BENESBY Quentin / COUSSON Sophie
    Creation     : 22-03-2022
    Modification : 28-03-2022
*/

/* score.h */

#ifndef __score__
#define __score__

    #include "partie.h"

    int score_mot(char* mot);
    void met_a_jour_score(Partie* partie, char* mot);

#endif
