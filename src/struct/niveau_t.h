// Structure de donnée représentant un niveau
typedef struct
{
	int lignes; // Nombre de lignes du niveau (hauteur en cases)
	int colonnes; // Nombre de colonnes du niveau (largeur en cases)
	char* terrain; // Contenu du niveau sous forme de caractères
} niveau_t;

// Crée un nouveau niveau de taille nb_colonnes * nb_lignes et retourne un pointeur vers l'instance créée
niveau_t* nouveau_niveau (int nb_colonnes, int nb_lignes);

// Supprime une instance de type niveau_t passée en paramètre avec son pointeur
void detruire_niveau (niveau_t* niveau);

// Détermine pour le niveau spéfcifié l'indice du tableau terrain correspondant aux coordonnées spécifiées
int indice_case_sur_terrain (niveau_t* niveau, int colonne, int ligne);

// Modifie une case du terrain du niveau passé en paramètre et la remplace par car
void place_sur_terrain (niveau_t* niveau, int colonne, int ligne, char car);

// Lis le contenu du terrain aux coordonées spécifiées en paramètre
char lecture_du_terrain (niveau_t* niveau, int colonne, int ligne);

void initialise_terrain(niveau_t* niveau);

void affichage_niveau(niveau_t* niveau);

niveau_t* lecture_du_niveau(int quel_niveau);
