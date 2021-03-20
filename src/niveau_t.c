#include "../include/main.h"

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
	return ligne * niveau->colonnes + colonne;
}

void coordonnees_par_indice (niveau_t* niveau, int indice, int* colonne, int* ligne){
  *ligne = (int)(indice / niveau->colonnes);
  *colonne = (int)(indice % niveau->colonnes);
}

int taille_tableau_terrain (niveau_t* niveau){
  return niveau->lignes * niveau->colonnes;
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
  for (int ligne = 0; ligne < niveau->lignes; ligne++){
    for (int colonne = 0; colonne < niveau->colonnes; colonne++){
      printf("%c", lecture_du_terrain(niveau, colonne, ligne));
      //printf("AFFICHAGE DE %d %d\n", colonne, ligne);
    }
    printf("\n");
  }
  /*printf("T=%d\n", taille_tableau_terrain(niveau));
  for (int i = 0; i < taille_tableau_terrain(niveau); ++i){
    //printf("%s", niveau->terrain[i] == EOF ? "." : "-");
    char c = niveau->terrain[i];
    printf("%d (%c)\t\n", c, c);
  }*/
}

niveau_t* lecture_du_niveau(int quel_niveau){
  FILE* fichier;
  char chemin_du_niveau[100];
  sprintf(chemin_du_niveau,"./niveau/niveau_%d", quel_niveau);
  fichier = fopen(chemin_du_niveau, "r");
  
  int colonne;
  int ligne;
  
  fscanf(fichier, "%d %d", &colonne, &ligne);
  niveau_t* niveau = nouveau_niveau(colonne, ligne);

  char car = fgetc(fichier);
  int terrainIdx = 0;
  int taille_tab_terrain = taille_tableau_terrain(niveau);

  while(car != EOF && terrainIdx <= taille_tab_terrain)
  {
    coordonnees_par_indice(niveau, terrainIdx, &colonne, &ligne);

    if (car != '\r' && car != '\n'){
      place_sur_terrain(niveau, colonne, ligne, car);
      //printf("%d\n",lecture_du_terrain(niveau, colonne, ligne));
      ++terrainIdx;
    }

    car = fgetc(fichier);
  }
  printf("\n");
  fclose(fichier);
  return niveau;
}

void liberation_du_niveau(niveau_t* niveau){

}
/*
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
*/
