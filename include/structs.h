#ifndef TYPES_H_
#define TYPES_H_

// Structure de donnée représentant un joueur
typedef struct{
  int ligne; // Coordonnée verticale (Y)
  int colonne; // Coordonnée horizontale (X)
} perso_t;

// Structure de donnée représentant un niveau
typedef struct{
  int lignes; // Nombre de lignes du niveau (hauteur en cases)
  int colonnes; // Nombre de colonnes du niveau (largeur en cases)
  char* terrain; // Contenu du niveau sous forme de caractères
} niveau_t;

#endif // TYPES_H_