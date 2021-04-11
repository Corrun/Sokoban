#ifndef POINT_H_
#define POINT_H_

//Fonction inutilisée mais demandée, voir fonction : "affichage_niveau_ncurses()"
//char entree_du_joueur(void);

point_t* nouveau_point(int colonne, int ligne);

point_t* trouver_perso(niveau_t* niveau);

#endif // POINT_H_