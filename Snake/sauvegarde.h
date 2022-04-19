/* sauvegarde.h */

#ifndef __sauvegarde__
#define __sauvegarde__

    #include <stdio.h>
    
    typedef struct {
        int largeur;
        int hauteur;
        int nb_pommes;
        int taille_serp;
        int raffraichissement;
    }Partie;

    int entier_fichier(char* chaine, int taille);
    void lis_fichier(Partie* p) ;

#endif
