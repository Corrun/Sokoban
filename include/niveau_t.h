#ifndef NIVEAU_T_H_
#define NIVEAU_T_H_

/*
 * On utilise un tableau dynamique de niveau_t* pour stocker les
 * etats du jeu au fur et a mesure que le joueur avance. Ainsi,
 * etats_niveaux->memoire[0] est l'etat initial du jeu, et
 * etats_niveaux->memoire[etats_niveaux->taille - 1] est l'etat courant.
 * A chaque deplacement reussi, on ajoute une entree a la liste.
 * A chaque annulation, on enleve le dernier element de la liste si il y en a plus qu'un.
 */
extern liste_niveaux_t* etats_niveaux;

liste_niveaux_t *nouvelle_liste_niveaux (int taille);
void init_liste_niveaux (liste_niveaux_t* liste, int taille);
void liberation_de_la_liste_niveaux (liste_niveaux_t* liste);
void ajouter_niveau (liste_niveaux_t* liste, niveau_t* niveau);
void enlever_dernier_niveau (liste_niveaux_t* liste);
niveau_t* haut_de_liste (liste_niveaux_t* liste);

niveau_t* nouveau_niveau (int nb_colonnes, int nb_lignes);

void liberation_du_niveau (niveau_t* niveau);

int coordonnees_vers_indice_terrain (niveau_t* niveau, int colonne, int ligne);

void indice_vers_coordonnees_niveau (niveau_t* niveau, int indice, int* colonne, int* ligne);

int taille_tableau_terrain (niveau_t* niveau);

void place_sur_terrain (niveau_t* niveau, int colonne, int ligne, char car);

void place_sur_terrain_par_coordonnees (niveau_t* niveau, point_t* coord, char car);

char lecture_du_terrain (niveau_t* niveau, int colonne, int ligne);

char lecture_du_terrain_par_coordonnees (niveau_t* niveau, point_t* coord);

void initialise_terrain (niveau_t* niveau);

char affichage_niveau_ncurses (niveau_t* niveau);

int modification_affichage_niveau (niveau_t* niveau, int x, int y, char* symbole);

void affichage_niveau (niveau_t* niveau);

niveau_t* lecture_du_niveau (int quel_niveau);

void analyser_case_niveau (niveau_t* niveau, int indice);

void deplacement (niveau_t* niveau, char direction);

bool case_libre_sur_terrain (niveau_t* niveau, int colonne, int ligne);

bool caisse_sur_terrain (niveau_t* niveau, int colonne, int ligne);

int nombre_de_caisse_restante_sur_terrain (niveau_t* niveau);

niveau_t* copier_niveau (niveau_t *source);

void annuler_deplacement();

#endif // NIVEAU_T_H_

