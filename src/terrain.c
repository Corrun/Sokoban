#include "main.h"

void initialise_terrain (niveau_t* niveau){
  // On parcours les indices du terrain pour placer des murs sur chaque case
  for (int indice = 0; indice < taille_tableau_terrain(niveau); ++indice) {
    // On place un mur sur la case n°indice
    niveau->terrain[indice] = TILE_WALL;
  }
}

// Modifie une case du terrain du niveau passé en paramètre et la remplace par car
void place_sur_terrain (niveau_t* niveau, int colonne, int ligne, char car) {
	// On calcule l'indice de la case à modifier
	int indice = coordonnees_vers_indice_terrain(niveau, colonne, ligne);

	// On remplace la valeur par car
	niveau->terrain[indice] = car;
}

// Modifie une case du terrain du niveau passé en paramètre sous forme de point_t et la remplace par car
void place_sur_terrain_par_coordonnees (niveau_t* niveau, point_t* coord, char car) {
	place_sur_terrain(niveau, coord->colonne, coord->ligne, car);
}

// Lis le contenu du terrain aux coordonées spécifiées en paramètre
char lecture_du_terrain (niveau_t* niveau, int colonne, int ligne) {
	// On calcule l'indice de la case à lire
	int indice = coordonnees_vers_indice_terrain(niveau, colonne, ligne);

	return niveau->terrain[indice];
}

// Effectue une lecture du terrain aux coordonnées spécifiées sous forme de point_t
char lecture_du_terrain_par_coordonnees (niveau_t* niveau, point_t* coord) {
	// On vérifie que les coordonnées sont valides
  // Si elles ne sont pas dans le terrain, on retourne \0 (NUL)
	if (coord->colonne < 0 || coord->colonne >= niveau->colonnes || coord->ligne < 0 || coord->ligne >= niveau->lignes){
    return '\0';
  }else{
    return niveau->terrain[coordonnees_vers_indice_terrain(niveau, coord->colonne, coord->ligne)];
  }
}

// Renvoie la longueur du tableau terrain du niveau spécifié
int taille_tableau_terrain (niveau_t* niveau) {
  return niveau->lignes * niveau->colonnes;
}