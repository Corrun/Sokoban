#include <stdlib.h>
#include "niveau_t.h"
#include "../constants.h"

niveau_t* nouveau_niveau (int nb_colonnes, int nb_lignes){
	// Allocation de l'espace mémoire pour l'instance du niveau
	niveau_t* niveau = malloc(sizeof(niveau_t));

	// On assigne les valeurs des attributs de niveau_t
	niveau->colonnes = nb_colonnes;
	niveau->lignes = nb_lignes;

	// On alloue un nouvel espace mémoire pour le terrain de nb_colonnes * nb_lignes cases
	niveau->terrain = malloc(sizeof(char) * nb_colonnes * nb_lignes);

	return niveau;
}

void detruire_niveau (niveau_t* niveau){
	// On libère la mémoire du terrain avant celle de l'instance
	// Sinon on a une fuite de mémoire car on ne peut plus référencer niveau->terrain
	free(niveau->terrain);
	free(niveau);
}

int indice_case_sur_terrain (niveau_t* niveau, int colonne, int ligne){
	// On calcule la position dans le tableau terrain
	// Lecture de gauche à droite puis de haut en bas
	return colonne * niveau->lignes + ligne;
}

void place_sur_terrain (niveau_t* niveau, int colonne, int ligne, char car){
	// On calcule l'indice de la case à modifier
	int indice = indice_case_sur_terrain(niveau, colonne, ligne);

	// On remplace la valeur par car
	niveau->terrain[indice] = car;
}

char lecture_du_terrain (niveau_t* niveau, int colonne, int ligne){
	// On calcule l'indice de la case à lire
	int indice = indice_case_sur_terrain(niveau, colonne, ligne);

	return niveau->terrain[indice];
}