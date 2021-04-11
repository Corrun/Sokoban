#ifndef POINT_H_
#define POINT_H_

char entree_du_joueur(void); // FIXME: Déplacer dans un fichier séparé (cf: input.h)

point_t* nouveau_point(int colonne, int ligne);

point_t* trouver_perso(niveau_t* niveau);

#endif // POINT_H_