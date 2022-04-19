/* graphique.h */

#ifndef __graphique__
#define __graphique__

    #include "monde.h"

    int debut_x(Partie p);
    int debut_y(Partie p);
    void interface_afficher_quadrillage(Monde mon, int nb_colonnes, int nb_lignes);
    void interface_afficher_pomme(Pomme pom, Partie p);
    void dessine_tete(Partie p, int x, int y);
    void dessine_corps(Partie p, int x, int y);
    void interface_afficher_serpent(Serpent ser, Partie p);
    void interface_affiche_murs(int x, int y);
    void pause_espace();
    void interface_piloter(Monde* mon);
    void interface_afficher_monde(Monde mon, Partie p);

#endif
