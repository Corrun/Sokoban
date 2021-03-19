#include <stdlib.h>
#include <stdio.h>
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

void initialise_terrain(niveau_t* niveau){
  int indice;
  for(int i = 0; i < niveau->colonnes ;i++){
    for(int y = 0; y < niveau->lignes ; y++){
      indice = indice_case_sur_terrain(niveau, i, y);
      niveau->terrain[indice] = TILE_WALL;
    }
  }
}

void affichage_niveau(niveau_t* niveau){
  int indice;
  for(int i = 0; i < niveau->colonnes;i++){
    for(int y = 0; y < niveau->lignes; y++){
      indice = indice_case_sur_terrain(niveau, i, y);
      printf("%c",niveau->terrain[indice]);
    }printf("\n");
  }
}

niveau_t* lecture_du_niveau(int quel_niveau){
  niveau_t* a = nouveau_niveau(10,7); 
  FILE* fichier;
  char chemin_du_niveau[100];
  printf("vla le fichier ouvert \n");
  //sprintf(chemin_du_niveau,"./../../niveau/niveau_%d",quel_niveau);
  sprintf(chemin_du_niveau,"niveau_%d",quel_niveau);
  printf("%s\n",chemin_du_niveau);
  fichier = fopen(chemin_du_niveau,"r");

  if(fichier == NULL){
    printf("null null le fichier nuull !\n");
  }
  
  char c;
  printf("On début le parcours de fichier \n");
  while ((c = fgetc(fichier)) != EOF){
    printf("%c",c);
  }

  fclose(fichier);
  
  return a;
}
