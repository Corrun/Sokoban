#ifndef NIVEAU_T_H_
#define NIVEAU_T_H_

// Structure de donnée représentant un niveau


// Crée un nouveau niveau de taille nb_colonnes * nb_lignes et retourne un pointeur vers l'instance créée
niveau_t* nouveau_niveau (int nb_colonnes, int nb_lignes);

// Supprime une instance de type niveau_t passée en paramètre avec son pointeur
void detruire_niveau (niveau_t* niveau);

// Détermine pour le niveau spéfcifié l'indice du tableau terrain correspondant aux coordonnées spécifiées
int indice_case_sur_terrain (niveau_t* niveau, int colonne, int ligne);

void coordonnees_par_indice (niveau_t* niveau, int indice, int* colonne, int* ligne);

int taille_tableau_terrain (niveau_t* niveau);

// Modifie une case du terrain du niveau passé en paramètre et la remplace par car
void place_sur_terrain (niveau_t* niveau, int colonne, int ligne, char car);

// Lis le contenu du terrain aux coordonées spécifiées en paramètre
char lecture_du_terrain (niveau_t* niveau, int colonne, int ligne);

void initialise_terrain(niveau_t* niveau);

void affichage_niveau(niveau_t* niveau);

niveau_t* lecture_du_niveau(int quel_niveau);

#endif // NIVEAU_T_H_