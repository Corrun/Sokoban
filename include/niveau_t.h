#ifndef NIVEAU_T_H_
#define NIVEAU_T_H_

niveau_t* nouveau_niveau (int nb_colonnes, int nb_lignes);

void detruire_niveau (niveau_t* niveau);

// RENAME: 
int indice_case_sur_terrain (niveau_t* niveau, int colonne, int ligne);

// RENAME: 
void coordonnees_par_indice (niveau_t* niveau, int indice, int* colonne, int* ligne);

int taille_tableau_terrain (niveau_t* niveau);

void place_sur_terrain (niveau_t* niveau, int colonne, int ligne, char car);

char lecture_du_terrain (niveau_t* niveau, int colonne, int ligne);

void initialise_terrain(niveau_t* niveau);

void affichage_niveau(niveau_t* niveau);

niveau_t* lecture_du_niveau(int quel_niveau);

#endif // NIVEAU_T_H_