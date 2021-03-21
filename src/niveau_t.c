#include "main.h"

// Crée un nouveau niveau de taille nb_colonnes * nb_lignes et retourne un pointeur vers l'instance créée
niveau_t* nouveau_niveau (int nb_colonnes, int nb_lignes){
	// Allocation de l'espace mémoire pour l'instance du niveau
	niveau_t* niveau = malloc(sizeof(niveau_t));

	// On assigne les valeurs des attributs de niveau_t
	niveau->colonnes = nb_colonnes;
	niveau->lignes = nb_lignes;

	// On alloue un nouvel espace mémoire pour le terrain de nb_colonnes * nb_lignes cases
	niveau->terrain = malloc(sizeof(char) * nb_colonnes * nb_lignes);

  // Les coordonnées du joueur sont pour le moment inconnues...
  niveau->perso = NULL;

	return niveau;
}

// Supprime une instance de type niveau_t passée en paramètre avec son pointeur
void liberation_du_niveau (niveau_t* niveau){
	// On libère la mémoire du terrain avant celle de l'instance
	// Sinon on a une fuite de mémoire car on ne peut plus référencer niveau->terrain
	free(niveau->terrain);
	free(niveau);
}

// Détermine pour le niveau spéfcifié l'indice du tableau terrain correspondant aux coordonnées spécifiées
int coordonnees_vers_indice_terrain (niveau_t* niveau, int colonne, int ligne){
	// On calcule la position dans le tableau terrain
	// Lecture de gauche à droite puis de haut en bas
	return ligne * niveau->colonnes + colonne;
}

// Fonction prenant un indice du tableau terrain et renvoyant la ligne/colonne correspondante
void indice_vers_coordonnees_niveau (niveau_t* niveau, int indice, int* colonne, int* ligne){
  *ligne = (int)(indice / niveau->colonnes);
  *colonne = (int)(indice % niveau->colonnes);
}

// Renvoie la longueur du tableau terrain du niveau spécifié
int taille_tableau_terrain (niveau_t* niveau){
  return niveau->lignes * niveau->colonnes;
}

// Modifie une case du terrain du niveau passé en paramètre et la remplace par car
void place_sur_terrain (niveau_t* niveau, int colonne, int ligne, char car){
	// On calcule l'indice de la case à modifier
	int indice = coordonnees_vers_indice_terrain(niveau, colonne, ligne);

	// On remplace la valeur par car
	niveau->terrain[indice] = car;
}

// Lis le contenu du terrain aux coordonées spécifiées en paramètre
char lecture_du_terrain (niveau_t* niveau, int colonne, int ligne){
	// On calcule l'indice de la case à lire
	int indice = coordonnees_vers_indice_terrain(niveau, colonne, ligne);

	return niveau->terrain[indice];
}

void initialise_terrain(niveau_t* niveau){
  // On parcours les indices du terrain pour placer des murs sur chaque case
  for (int indice = 0; indice < taille_tableau_terrain(niveau); ++indice){
    // On place un mur sur la case n°indice
    niveau->terrain[indice] = TILE_WALL;
  }
}

// Afficher le contenu du niveau dans le terminal
void affichage_niveau(niveau_t* niveau){
  // On "visite" le niveau par ligne puis par colonne
  for (int ligne = 0; ligne < niveau->lignes; ligne++){
    for (int colonne = 0; colonne < niveau->colonnes; colonne++){
      // On affiche le contenu de la case de coordonnées (colonne;ligne)
      printf("%c", lecture_du_terrain(niveau, colonne, ligne));
    }
    printf("\n"); // Retour à la ligne
  }
}

// Lire un niveau depuis un fichier (dans niveau/)
niveau_t* lecture_du_niveau (int numero_niveau){
  FILE* fichier;
  char chemin_du_niveau[100];

  sprintf(chemin_du_niveau,"./niveau/niveau_%d", numero_niveau);
  fichier = fopen(chemin_du_niveau, "r"); // On ouvre le fichier en lecture
  
  int colonne, ligne; // Variables pour stocker les coordonnées
  
  fscanf(fichier, "%d %d", &colonne, &ligne); // On lit la taille du niveau dans le fichier

  // On créée un niveau en mémoire avec les coordonnées lues
  niveau_t* niveau = nouveau_niveau(colonne, ligne);

  char car = fgetc(fichier); // On récupère le prochain caractère du fichier
  int indice_terrain = 0;
  int taille_tab_terrain = taille_tableau_terrain(niveau);

  while(car != EOF && indice_terrain <= taille_tab_terrain)
  {
    indice_vers_coordonnees_niveau(niveau, indice_terrain, &colonne, &ligne);

    // Si le caractère n'est pas un retour à la ligne
    if (car != '\r' && car != '\n'){
      // On place le caractère lu sur le terrain puis on incrépente
      // l'adresse/l'indice d'écriture
      place_sur_terrain(niveau, colonne, ligne, car);


      ++indice_terrain;
    }

    car = fgetc(fichier); // On récupère le prochain caractère du fichier
  }
  
  fclose(fichier); // On oublie pas de fermer le fichier :D
  return niveau;
}

// Analyse la case à un indice donné et modifie les propriétés de niveau en conséquences
void analyser_case_niveau (niveau_t* niveau, int indice){
  int colonne, ligne;

  // On obtient les coordonnées de la case du terrain
  indice_vers_coordonnees_niveau(niveau, indice, &colonne, &ligne);

  // On lit la case du terrain
  char car = lecture_du_terrain(niveau, colonne, ligne);

  switch (car){
    case TILE_PLAYER: // Si la case est un joueur, on modifie niveau->perso
      niveau->perso = nouveau_point(colonne, ligne);
      break;
  }
}

// Déplacer le joueur (si possible) dans la direction indiquée
void deplacement (niveau_t* niveau, char direction){ // TODO: Implement
  point_t* un_en_avant, deux_en_avant;

  switch (direction){
    case DIR_UP:
      

      break;
  }
}