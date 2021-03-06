#ifndef STRUCTS_H_
#define STRUCTS_H_

// Structure de donnée représentant la position du joueur
typedef struct point_t {
  int ligne; // Coordonnée verticale (Y)
  int colonne; // Coordonnée horizontale (X)
} point_t;

// Structure de donnée représentant un niveau
typedef struct niveau_t {
  int lignes; // Nombre de lignes du niveau (hauteur en cases)
  int colonnes; // Nombre de colonnes du niveau (largeur en cases)
  char* terrain; // Contenu du niveau sous forme de caractères
  point_t* perso; // Position du personnage
  int indice; // Indice dans la liste de niveaux
} niveau_t;

// Représente un tableau* de niveaux (pour la fonction d'annulation de déplacements)
// *pile/stack
typedef struct liste_niveaux_t {
  niveau_t** memoire; // Contient les pointeurs vers les instances de niveaux représentant des états précédents
  int taille; // Nombre de cases utilisées
  int taille_memoire; // Nombre de cases disponibles
} liste_niveaux_t;

// Représente une paire score/nom joueur 
typedef struct score_t {
  int score; //Score
  char nom[9]; //Nom du joueur
} score_t;

// Représente une liste de scores de taille fixe (top 5)
typedef struct liste_score_t {
  score_t** memoire; // Ensemble des scores
  int taille; // Nombre de score stockés (MAX 5)
} liste_score_t;

#endif // STRUCTS_H_