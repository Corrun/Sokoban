#ifndef STRUCTS_H_
#define STRUCTS_H_

// Structure de donnée représentant des coordonnées 2D
typedef struct{
  int ligne; // Coordonnée verticale (Y)
  int colonne; // Coordonnée horizontale (X)
} point_t;

// Structure de donnée représentant un niveau
typedef struct niveau_t {
  int lignes; // Nombre de lignes du niveau (hauteur en cases)
  int colonnes; // Nombre de colonnes du niveau (largeur en cases)
  char* terrain; // Contenu du niveau sous forme de caractères
  point_t* perso; // Position du personnage
  int nb_de_pas; // Nombre de pas réalisé dans un niveau
  struct niveau_t* etat_precedent_niveau; // Etat precedent du niveau, permet de revenir en arrière
} niveau_t;

#endif // STRUCTS_H_