typedef struct{
  int lignes;
  int colonnes;
}point_t;

typedef struct{
  int lignes; // Nombre de lignes du niveau (hauteur en cases)
  int colonnes; // Nombre de colonnes du niveau (largeur en cases)
  char* terrain; // Contenu du niveau sous forme de caractères
  point_t* perso;
}niveau_t;
