#ifndef NIVEAU_T_H_
#define NIVEAU_T_H_

niveau_t* nouveau_niveau (int nb_colonnes, int nb_lignes);

void liberation_du_niveau (niveau_t* niveau);

int coordonnees_vers_indice_terrain (niveau_t* niveau, int colonne, int ligne);

void indice_vers_coordonnees_niveau (niveau_t* niveau, int indice, int* colonne, int* ligne);

int taille_tableau_terrain (niveau_t* niveau);

void place_sur_terrain (niveau_t* niveau, int colonne, int ligne, char car);

char lecture_du_terrain (niveau_t* niveau, int colonne, int ligne);

void initialise_terrain (niveau_t* niveau);

void affichage_niveau (niveau_t* niveau);

niveau_t* lecture_du_niveau (int quel_niveau);

void analyser_case_niveau (niveau_t* niveau, int indice);

#endif // NIVEAU_T_H_