#include "../include/main.h"

char entree_du_joueur(void){
  int var;
  do
  {
    var = getchar();
  } while (var != 'z' && var != 'q' && var != 's' && var != 'd');
  printf("%c\n",var);
  return var;
}

point_t* nouveau_personnage(int colonne, int ligne){
  point_t* perso = malloc(sizeof(point_t));

  perso->colonnes = colonne;
	perso->lignes = ligne;
  return perso;
}

point_t* trouver_perso(niveau_t* niveau){
  for (int ligne = 0; ligne < niveau->lignes; ligne++){
    for (int colonne = 0; colonne < niveau->colonnes; colonne++){
      if(lecture_du_terrain(niveau, colonne, ligne)=='*'){
        point_t* perso = nouveau_personnage(colonne,ligne);
        return perso;
      }
    }
  }
  return NULL;
}
