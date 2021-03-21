#include "main.h"

char entree_du_joueur(void){
  int var;
  do
  {
    var = getchar();
  } while (var != 'z' && var != 'q' && var != 's' && var != 'd');
  printf("%c\n",var);
  return var;
}

// Créée une instance de personnage et retourne un pointeur vers cette dernière
perso_t* nouveau_personnage (void){
  return malloc(sizeof(perso_t));
}

void initialise_personnage (perso_t* personnage, int colonne, int ligne){
  // Modification des attributs
  personnage->colonne = colonne;
	personnage->ligne = ligne;
}

// Parcours le terrain d'un niveau et renvoie un nouveau personnage
perso_t* trouver_perso(niveau_t* niveau){
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
    perso_t* personnage = nouveau_personnage();
    initialise_personnage(personnage, colonne, ligne);

    return personnage;
  }

  // Si le niveau ne comporte pas de case personnage, on retourne un pointeur nul
  return NULL;
}