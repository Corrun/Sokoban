#include "main.h"

// Déplace le joueur (si possible) dans la direction indiquée
void deplacement (niveau_t* n, char direction){
  // Pointeurs vers 1/2 case(s) en avant avant de se déplacer
  point_t *un_en_avant, *deux_en_avant;

  // On copie le niveau afin de ne pas modifier l'état précédent (par même référence mémoire)
  niveau_t* niveau = copier_niveau(n);
  
  // On calcule les coordonnées des cases un pas et deux pas en avant (en fonction de la direction)
  switch (direction){
    case DIR_UP: // Direction choisie : HAUT
      un_en_avant = nouveau_point(niveau->perso->colonne + 0, niveau->perso->ligne - 1);
      deux_en_avant = nouveau_point(niveau->perso->colonne + 0, niveau->perso->ligne - 2);
      break;
    case DIR_DOWN: // Direction choisie : BAS
      un_en_avant = nouveau_point(niveau->perso->colonne + 0, niveau->perso->ligne + 1);
      deux_en_avant = nouveau_point(niveau->perso->colonne + 0, niveau->perso->ligne + 2);
      break;
    case DIR_LEFT: // Direction choisie : GAUCHE
      un_en_avant = nouveau_point(niveau->perso->colonne - 1, niveau->perso->ligne + 0);
      deux_en_avant = nouveau_point(niveau->perso->colonne - 2, niveau->perso->ligne + 0);
      break;
    case DIR_RIGHT: // Direction choisie : DROITE
      un_en_avant = nouveau_point(niveau->perso->colonne + 1, niveau->perso->ligne + 0);
      deux_en_avant = nouveau_point(niveau->perso->colonne + 2, niveau->perso->ligne + 0);
      break;
    default: // Direction invalide
      return;
  }

  // Si il y a une caisse devant nous, et que la case d'après est libre, on pousse la caisse
  if (caisse_sur_terrain(niveau, un_en_avant->colonne, un_en_avant->ligne)
    && case_libre_sur_terrain(niveau, deux_en_avant->colonne, deux_en_avant->ligne)){
    // On remplace la case en face par une case libre du bon type (cible/vide)
    switch(lecture_du_terrain_par_coordonnees(niveau, un_en_avant)){
      // Si la case en face est une caisse sur une cible
      case TILE_CRATE_ON_TARGET: 
        //On remplace par une cible
        place_sur_terrain_par_coordonnees(niveau, un_en_avant, TILE_TARGET);
        break;
      // Si la case en face est une caisse simple
      case TILE_CRATE: 
        //On remplace par le néant le plus total
        place_sur_terrain_par_coordonnees(niveau, un_en_avant, TILE_EMPTY);
        break;
    }

    // On remplace la case un cran plus loin (que la case en face) par une case du bon type (caisse/caisse sur cible)
    switch(lecture_du_terrain_par_coordonnees(niveau, deux_en_avant)){
      // Si la case deux pas en avant est vide
      case TILE_EMPTY: 
        //On place une caisse
        place_sur_terrain_par_coordonnees(niveau, deux_en_avant, TILE_CRATE);
        break;
      // Si la case deux pas en avant est une cible
      case TILE_TARGET: 
        //On remplace par une caisse sur une cible
        place_sur_terrain_par_coordonnees(niveau, deux_en_avant, TILE_CRATE_ON_TARGET);
        break;
    }
  }
  
  // Si la case d'en face est libre
  if (case_libre_sur_terrain(niveau, un_en_avant->colonne, un_en_avant->ligne)) {
    // On "déplace" le personnage
    niveau->perso->colonne = un_en_avant->colonne;
    niveau->perso->ligne = un_en_avant->ligne;
    //On ajoute un niveau dans "etats_niveaux"
    ajouter_niveau(etats_niveaux, niveau);
  } else {
    //On libère la mémoire alouée par le niveau
    liberation_du_niveau(niveau); 
  }

  //On libère la mémoire alouée par "un_en_avant"
  free(un_en_avant);
  //On libère la mémoire alouée par "deux_en_avant"
  free(deux_en_avant);
}

// Annule le dernier déplacement
void annuler_deplacement(void) {
  //Si le joueur a effectuer au moins une action, reviens à la dernière position
  if (etats_niveaux->taille > 1) enlever_dernier_niveau (etats_niveaux);
}