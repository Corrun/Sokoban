#ifndef TYPES_H_
#define TYPES_H_

typedef struct{
  int lignes;
  int colonnes;
} point_t;

// Structure de donnée représentant un niveau
typedef struct{
  int lignes; // Nombre de lignes du niveau (hauteur en cases)
  int colonnes; // Nombre de colonnes du niveau (largeur en cases)
  char* terrain; // Contenu du niveau sous forme de caractères
  point_t* perso; // TODO: Déplacer dans un typedef spécifique
} niveau_t;

#endif // TYPES_H_