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
  // On commence par définir une variable indice qui nous servira pour plus tard
  int indice;
  
  for(int i = 0; i < niveau->colonnes ;i++){ //On boucle ...
    for(int y = 0; y < niveau->lignes ; y++){ // ... sur le tableau
      
      // On se sert d'une fonction géniale qui permet d'accéder a une case du tableau sans soucis
      indice = indice_case_sur_terrain(niveau, i, y);

      // Et on rempli le terrain de mur ...
      niveau->terrain[indice] = TILE_WALL;
    }
  }
}

void affichage_niveau(niveau_t* niveau){
  // On commence par définir une variable indice qui nous servira pour plus tard
  int indice;

  // On fait un retour à la ligne pour être sûr que la dernière fonction utilisée ne nous
  // ai pas laissée en plein millieu du terminal 
  printf("\n");
  
  for(int i = 0; i < niveau->colonnes;i++){ // On boucle ...
    for(int y = 0; y < niveau->lignes; y++){ // ... sur le tableau

      // On se sert d'une fonction géniale qui permet d'accéder a une case du tableau sans soucis
      indice = indice_case_sur_terrain(niveau, i, y);

      // On affiche le contenu de la case sur laquelle l'indice pointe
      printf("%c",niveau->terrain[indice]);
    }printf("\n"); // Retour à la ligne pour éviter d'avoir un tableau à une dimmension..visuellement...
  }
}

// Faut débug avant qq même :>
niveau_t* lecture_du_niveau(int quel_niveau){
  FILE* fichier;
  char chemin_du_niveau[100];
  sprintf(chemin_du_niveau,"./niveau/niveau_%d",quel_niveau);
  fichier = fopen(chemin_du_niveau,"r");
  int colonne;
  int ligne;
  char c;
  fscanf(fichier,"%d %d",&colonne,&ligne);
  //printf(">%d %d<\n", i,y);
  niveau_t* niveau = nouveau_niveau(colonne,ligne);

  for(int idx = 0; idx < colonne * ligne ; idx ++){
    printf("%c",c);
    if((c = fgetc(fichier))==EOF){
      break;
    }else{
      if(c == ' '){
	niveau->terrain[idx] = TILE_EMPTY;
      }else if(c == '#'){
	niveau->terrain[idx] = TILE_WALL;
      }else if(c == '$'){
	niveau->terrain[idx] = TILE_CRATE;
      }else if(c == '.'){
	niveau->terrain[idx] = TILE_CRATE_ON_TARGET;
      }else if(c == '*'){
	niveau->terrain[idx] = TILE_PLAYER;
      }else if(c == '+'){
	niveau->terrain[idx] = TILE_PLAYER_ON_TARGET;
      }else{
	niveau->terrain[idx] = TILE_EMPTY;
      }      
     }
  }
  printf("\n");
  fclose(fichier);
  return niveau;
}
