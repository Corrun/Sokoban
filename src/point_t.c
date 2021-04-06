#include "main.h"

char entree_du_joueur (void){
  int var;
  do
  {
    var = getchar();
    var = majuscule_en_minuscule(var);    
  } while (var != DIR_UP && var != DIR_LEFT && var != DIR_DOWN && var != DIR_RIGHT && var != LEAVE);
  printf("%c\n",var);
  return var;
}

// Créée une instance d'un point avec les coordonnées spécifiées et renvoie un pointeur vers son adresse 
point_t* nouveau_point (int colonne, int ligne){
  // On alloue de la mémoire pour stocker un point
  point_t* point = malloc(sizeof(point_t));

  // Modification des attributs
  point->colonne = colonne;
	point->ligne = ligne;

  return point;
}

// Parcours le terrain d'un niveau et renvoie un nouveau personnage
point_t* trouver_perso (niveau_t* niveau){
  int index = 0; // Indice de parcours dans le tableau terrain du niveau

  // Tant que la case n'est pas un joueur et que l'indice est dans le tableau
  while (index < taille_tableau_terrain(niveau) && niveau->terrain[index] != TILE_PLAYER){
    ++index; // Incrémenter l'indice de parcours
  }

  // Si l'indice est une adresse valide du tableau terrain
  if (index < taille_tableau_terrain(niveau)){
    int colonne, ligne;

    // On récupère les coordonnées correspondantes à l'indice de parcours
    indice_vers_coordonnees_niveau(niveau, index, &colonne, &ligne);

    // On créée et initialise un nouveau personnage
    point_t* personnage = nouveau_point(colonne, ligne);

    return personnage;
  }

  // Si le niveau ne comporte pas de case personnage, on retourne un pointeur nul
  return NULL;
}

