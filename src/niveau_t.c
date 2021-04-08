#include "main.h"

liste_niveaux_t* etats_niveaux;

liste_niveaux_t* nouvelle_liste_niveaux (int taille) {
  liste_niveaux_t *resultat = malloc(sizeof(liste_niveaux_t));
  init_liste_niveaux (resultat, taille);
  return resultat;
}

void init_liste_niveaux (liste_niveaux_t* liste, int taille) {
  liste->memoire = malloc (sizeof (niveau_t *) * taille);
  liste->taille = 0;
  liste->taille_memoire = taille;
}

void liberation_de_la_liste_niveaux (liste_niveaux_t* liste)
{
  free (liste->memoire);
  liste->memoire = NULL;
  liste->taille = 0;
  liste->taille_memoire = 0;
}

void agrandir_liste_de_niveaux (liste_niveaux_t *liste, int ajout)
{
  if (ajout > 0)
  {
    niveau_t** nouveau = malloc (sizeof (niveau_t*) * (liste->taille_memoire + ajout));
    memcpy (nouveau, liste->memoire, sizeof (niveau_t*) * liste->taille);
    free (liste->memoire);
    liste->memoire = nouveau;
    liste->taille_memoire += ajout;
  }
}

void ajouter_niveau (liste_niveaux_t *liste, niveau_t* niveau)
{
  if (liste->taille == liste->taille_memoire) agrandir_liste_de_niveaux (liste, 10);

  liste->memoire[liste->taille] = niveau;
  niveau->indice = liste->taille;
  liste->taille += 1;
}

void enlever_dernier_niveau (liste_niveaux_t *liste)
{
  if (liste->taille > 0) {
    liberation_du_niveau (haut_de_liste(etats_niveaux));
    liste->taille -= 1;
  }
}

niveau_t* haut_de_liste (liste_niveaux_t* liste) {
  if (liste->taille == 0) return NULL;

  return liste->memoire[liste->taille - 1];
}

// Crée un nouveau niveau de taille nb_colonnes * nb_lignes et retourne un pointeur vers l'instance créée
niveau_t* nouveau_niveau (int nb_colonnes, int nb_lignes){
	// Allocation de l'espace mémoire pour l'instance du niveau
	niveau_t* niveau = malloc(sizeof(niveau_t));

	// On assigne les valeurs des attributs de niveau_t
	niveau->colonnes = nb_colonnes;
	niveau->lignes = nb_lignes;
  
	// On alloue un nouvel espace mémoire pour le terrain de nb_colonnes * nb_lignes cases
	niveau->terrain = malloc(sizeof(char) * nb_colonnes * nb_lignes);
  
  // Les coordonnées du joueur sont pour le moment inconnues...
  niveau->perso = NULL;

  // L'état précédent n'existe pas encore, on l'initialise
	return niveau;
}

// Supprime une instance de type niveau_t passée en paramètre avec son pointeur
void liberation_du_niveau (niveau_t* niveau) {
	// On libère la mémoire du terrain avant celle de l'instance
	// Sinon on a une fuite de mémoire car on ne peut plus référencer niveau->terrain
  free(niveau->perso);
	free(niveau->terrain);
	free(niveau);
}

// Détermine pour le niveau spéfcifié l'indice du tableau terrain correspondant aux coordonnées spécifiées
int coordonnees_vers_indice_terrain (niveau_t* niveau, int colonne, int ligne){
	// On calcule la position dans le tableau terrain
	// Lecture de gauche à droite puis de haut en bas
	return ligne * niveau->colonnes + colonne;
}

// Fonction prenant un indice du tableau terrain et renvoyant la ligne/colonne correspondante
void indice_vers_coordonnees_niveau (niveau_t* niveau, int indice, int* colonne, int* ligne){
  *ligne = (int)(indice / niveau->colonnes);
  *colonne = (int)(indice % niveau->colonnes);
}

// Renvoie la longueur du tableau terrain du niveau spécifié
int taille_tableau_terrain (niveau_t* niveau){
  return niveau->lignes * niveau->colonnes;
}

// Modifie une case du terrain du niveau passé en paramètre et la remplace par car
void place_sur_terrain (niveau_t* niveau, int colonne, int ligne, char car){
	// On calcule l'indice de la case à modifier
	int indice = coordonnees_vers_indice_terrain(niveau, colonne, ligne);

	// On remplace la valeur par car
	niveau->terrain[indice] = car;
}

// Modifie une case du terrain du niveau passé en paramètre sous forme de point_t et la remplace par car
void place_sur_terrain_par_coordonnees (niveau_t* niveau, point_t* coord, char car){
	place_sur_terrain(niveau, coord->colonne, coord->ligne, car);
}

// Lis le contenu du terrain aux coordonées spécifiées en paramètre
char lecture_du_terrain (niveau_t* niveau, int colonne, int ligne){
	// On calcule l'indice de la case à lire
	int indice = coordonnees_vers_indice_terrain(niveau, colonne, ligne);

	return niveau->terrain[indice];
}

// Effectue une lecture du terrain aux coordonnées spécifiées sous forme de point_t
char lecture_du_terrain_par_coordonnees (niveau_t* niveau, point_t* coord){
	// On vérifie que les coordonnées sont valides
  // Si elles ne sont pas dans le terrain, on retourne \0 (NUL)
	if (coord->colonne < 0 || coord->colonne >= niveau->colonnes || coord->ligne < 0 || coord->ligne >= niveau->lignes){
    return '\0';
  }else{
    return niveau->terrain[coordonnees_vers_indice_terrain(niveau, coord->colonne, coord->ligne)];
  }
}

void initialise_terrain(niveau_t* niveau){
  // On parcours les indices du terrain pour placer des murs sur chaque case
  for (int indice = 0; indice < taille_tableau_terrain(niveau); ++indice){
    // On place un mur sur la case n°indice
    niveau->terrain[indice] = TILE_WALL;
  }
}

char affichage_niveau_ncurses (niveau_t* niveau) {
  int yMax, xMax; // Taille de la console en caractères
	
	WINDOW* fenetre = nouvelle_fenetre(); // Nouvelle fenêtre

  while (true) {
    getmaxyx(stdscr, yMax, xMax); // Lire la taille de la console
		
		// Centrer la fenêtre
		centrer_fenetre(fenetre, niveau->lignes + 3, niveau->colonnes + 2, yMax, xMax, 0, 0);  

		effacer_ecran(); // Efface l'ecran
		
		wclear(fenetre); // Raffraichi la fenêtre
		box(fenetre, 0, 0); // Bordure de la fenêtre

    for (int ligne = 0; ligne < niveau->lignes; ++ligne) {
      for (int colonne = 0; colonne < niveau->colonnes; ++colonne) {
        //char case_terrain = lecture_du_terrain(niveau, colonne, ligne);
        char case_affichee = '\0';

        int attribut = modification_affichage_niveau(niveau, colonne, ligne, &case_affichee);

        wattron(fenetre, attribut);

        mvwaddch(fenetre, ligne + 1, colonne + 1, case_affichee);
        wattroff(fenetre, attribut);
        wrefresh(fenetre);
      }
    }
    
    //sprintf("Coups %c", niveau->nb_de_pas);
    wattron(fenetre, A_STANDOUT);
    mvwprintw(fenetre, 0, 2, "Titre"); // Titre de la fenetre
    char nb_coups[100];
    sprintf(nb_coups, "Coups: %d", etats_niveaux->taille - 1);
    
    mvwprintw(fenetre, niveau->lignes+1, niveau->colonnes + 1 - strlen(nb_coups), nb_coups);

    //mvwprintw(fenetre, niveau->lignes+1, niveau->colonnes-5, nb_coups); // Nombre de pas (actuellement à 0 vu que c'est l'initialisation du niveau)
    wattroff(fenetre, A_STANDOUT);

    int saisie = majuscule_en_minuscule(wgetch(fenetre));

    //int saisie = wgetch(fenetre);
    switch (saisie) {
      case KB_UP:
      case DIR_UP:
        return DIR_UP;
      case KB_DOWN:
      case DIR_DOWN:
        return DIR_DOWN;
      case KB_LEFT:
      case DIR_LEFT:
        return DIR_LEFT;
      case KB_RIGHT:
      case DIR_RIGHT:
        return DIR_RIGHT;
      case LEAVE:
      case RESTART:
      case CANCEL:
        return (char)saisie;
    }
  }
}

int modification_affichage_niveau (niveau_t* niveau, int x, int y, char* symbole) {
  char case_terrain = lecture_du_terrain(niveau, x, y);

  if (x == niveau->perso->colonne && y == niveau->perso->ligne) {
    switch (case_terrain) {
      case TILE_EMPTY:
        case_terrain = TILE_PLAYER;
        break;
      case TILE_TARGET:
        case_terrain = TILE_PLAYER_ON_TARGET;
        break;
    }
  }


  switch (case_terrain) {
    case TILE_EMPTY:
      *symbole = DISPLAY_TILE_EMPTY;
      break;
    case TILE_WALL:
      *symbole = DISPLAY_TILE_WALL;
      return A_DIM;
    case TILE_CRATE:
      *symbole = DISPLAY_TILE_CRATE;
      return COLOR_PAIR(COLOR_YELLOW);
    case TILE_TARGET:
      *symbole = DISPLAY_TILE_TARGET;
      break;
    case TILE_CRATE_ON_TARGET:
      *symbole = DISPLAY_TILE_CRATE_ON_TARGET;
      break;
    case TILE_PLAYER:
      *symbole = DISPLAY_TILE_PLAYER;
      return A_BOLD | COLOR_PAIR(COLOR_GREEN);
    case TILE_PLAYER_ON_TARGET:
      *symbole = DISPLAY_TILE_PLAYER_ON_TARGET;
      break;
  }

  return 0;
}

// Afficher le contenu du niveau dans le terminal
void affichage_niveau(niveau_t* niveau){
  // On "visite" le niveau par ligne puis par colonne
  for (int ligne = 0; ligne < niveau->lignes; ligne++){
    for (int colonne = 0; colonne < niveau->colonnes; colonne++){
      // Lecture de la case du terrain
      char car = lecture_du_terrain(niveau, colonne, ligne);
      switch (car){
        case TILE_EMPTY:
          car = DISPLAY_TILE_EMPTY;
          break;
        case TILE_WALL:
          car = DISPLAY_TILE_WALL;
          break;
        case TILE_CRATE:
          car = DISPLAY_TILE_CRATE;
          break;
        case TILE_TARGET:
          car = DISPLAY_TILE_TARGET;
          break;
        case TILE_CRATE_ON_TARGET:
          car = DISPLAY_TILE_CRATE_ON_TARGET;
          break;
        case TILE_PLAYER:
          car = DISPLAY_TILE_PLAYER;
          break;
        case TILE_PLAYER_ON_TARGET:
          car = DISPLAY_TILE_PLAYER_ON_TARGET;
          break;
      }
      // Si le joueur est sur la case
      if (niveau->perso->colonne == colonne && niveau->perso->ligne == ligne){
        switch(car){
          case TILE_EMPTY: // Si la case est vide, afficher un joueur
            car = DISPLAY_TILE_PLAYER;
            break;
           case TILE_TARGET: // Si la case est une cible, afficher un joueur sur une cible
            car = DISPLAY_TILE_PLAYER_ON_TARGET;
            break;
        }
      }
      
      // On affiche le contenu de la case de coordonnées (colonne;ligne)
      printf("%c", car);
    }
    printf("\n"); // Retour à la ligne
  }
}
/*
void affichage_niveau(niveau_t* niveau){
  char caractereTrouve;
 for (int ligne = 0; ligne < niveau->lignes; ligne++){
    for (int colonne = 0; colonne < niveau->colonnes; colonne++){
      switch (caractereTrouve){
        case TILE_EMPTY:
          caractereTrouve = DISPLAY_TILE_EMPTY;
          break;
        case TILE_WALL:
          caractereTrouve = DISPLAY_TILE_WALL;
          break;
        case TILE_CRATE:
          caractereTrouve = DISPLAY_TILE_CRATE;
          break;
        case TILE_TARGET:
          caractereTrouve = DISPLAY_TILE_TARGET;
          break;
        case TILE_CRATE_ON_TARGET:
          caractereTrouve = DISPLAY_TILE_CRATE_ON_TARGET;
          break;
        case TILE_PLAYER:
          caractereTrouve = DISPLAY_TILE_PLAYER;
          break;
        case TILE_PLAYER_ON_TARGET:
          caractereTrouve = DISPLAY_TILE_PLAYER_ON_TARGET;
          break;
        default:
          return;
      }

      printf("%c", caractereTrouve);
    }
  }

}*/

// Lire un niveau depuis un fichier (dans niveau/)
niveau_t* lecture_du_niveau (int numero_niveau){
  FILE* fichier;
  char chemin_du_niveau[100];

  sprintf(chemin_du_niveau,"./niveau/niveau_%d", numero_niveau);
  fichier = fopen(chemin_du_niveau, "r"); // On ouvre le fichier en lecture
  
  if (!fichier) {
    return NULL;
  }

  int colonne, ligne; // Variables pour stocker les coordonnées
  
  fscanf(fichier, "%d %d", &colonne, &ligne); // On lit la taille du niveau dans le fichier

  // On créée un niveau en mémoire avec les coordonnées lues
  niveau_t* niveau = nouveau_niveau(colonne, ligne);

  char car = fgetc(fichier); // On récupère le prochain caractère du fichier
  int indice_terrain = 0;
  int taille_tab_terrain = taille_tableau_terrain(niveau);

  while(car != EOF && indice_terrain <= taille_tab_terrain)
  {
    indice_vers_coordonnees_niveau(niveau, indice_terrain, &colonne, &ligne);

    // Si le caractère n'est pas un retour à la ligne
    if (car != '\r' && car != '\n'){
      // On place le caractère lu sur le terrain puis on incrépente
      // l'adresse/l'indice d'écriture
      place_sur_terrain(niveau, colonne, ligne, car);
      analyser_case_niveau(niveau, indice_terrain);

      ++indice_terrain;
    }

    car = fgetc(fichier); // On récupère le prochain caractère du fichier
  }
  
  fclose(fichier); // On oublie pas de fermer le fichier :D
  return niveau;
}

// Analyse la case à un indice donné et modifie les propriétés de niveau en conséquences
void analyser_case_niveau (niveau_t* niveau, int indice){
  int colonne, ligne;

  // On obtient les coordonnées de la case du terrain
  indice_vers_coordonnees_niveau(niveau, indice, &colonne, &ligne);

  // On lit la case du terrain
  char car = lecture_du_terrain(niveau, colonne, ligne);

  switch (car){
    case TILE_PLAYER: // Si la case est un joueur, on modifie niveau->perso
      niveau->perso = nouveau_point(colonne, ligne);
      place_sur_terrain(niveau, colonne, ligne, TILE_EMPTY);
      break;
  }
}

// Effectue une copie d'un niveau (pour stocker les états précédents)
// Cette copie s'assure que l'on a bien une référence distincte sur le terrain
// Au lieu d'ue copie du pointeur vers ce dernier
niveau_t* copier_niveau (niveau_t *source) {
  if (!source) return NULL;

  niveau_t *copie = malloc (sizeof (niveau_t));
  copie->lignes = source->lignes;
  copie->colonnes = source->colonnes;
  copie->terrain = malloc (sizeof (char) * taille_tableau_terrain(source));
  memcpy (copie->terrain, source->terrain, sizeof(char) * taille_tableau_terrain(source));
  copie->perso = malloc (sizeof (point_t));
  memcpy (copie->perso, source->perso, sizeof (point_t));

  return copie;
}

// Déplacer le joueur (si possible) dans la direction indiquée
void deplacement (niveau_t* n, char direction){
  point_t *un_en_avant, *deux_en_avant; // Pointeurs vers 1/2 case(s) en avant avant de se déplacer

  niveau_t* niveau = copier_niveau(n);
  
  // On calcule les coordonnées des case un pas et deux pas en avant (en fonction de la direction)
  switch (direction){
    case DIR_UP:
      un_en_avant = nouveau_point(niveau->perso->colonne + 0, niveau->perso->ligne - 1);
      deux_en_avant = nouveau_point(niveau->perso->colonne + 0, niveau->perso->ligne - 2);
      break;
    case DIR_DOWN:
      un_en_avant = nouveau_point(niveau->perso->colonne + 0, niveau->perso->ligne + 1);
      deux_en_avant = nouveau_point(niveau->perso->colonne + 0, niveau->perso->ligne + 2);
      break;
    case DIR_LEFT:
      un_en_avant = nouveau_point(niveau->perso->colonne - 1, niveau->perso->ligne + 0);
      deux_en_avant = nouveau_point(niveau->perso->colonne - 2, niveau->perso->ligne + 0);
      break;
    case DIR_RIGHT:
      un_en_avant = nouveau_point(niveau->perso->colonne + 1, niveau->perso->ligne + 0);
      deux_en_avant = nouveau_point(niveau->perso->colonne + 2, niveau->perso->ligne + 0);
      break;
    default: // Direction invalide
      return;
  }

  // Si caisse en face et case libre encore après, on pousse la caisse
  if (caisse_sur_terrain(niveau, un_en_avant->colonne, un_en_avant->ligne)
    && case_libre_sur_terrain(niveau, deux_en_avant->colonne, deux_en_avant->ligne))
  {
    // On remplace la case en face par une case libre du bon type (cible/vide)
    switch(lecture_du_terrain_par_coordonnees(niveau, un_en_avant)){
      case TILE_CRATE_ON_TARGET: // Si la case en face est une caisse sur une cible, on remplace par une cible
        place_sur_terrain_par_coordonnees(niveau, un_en_avant, TILE_TARGET);
        break;
      case TILE_CRATE: // Si la case en face est une caisse simple, on remplace par le néant le plus total
        place_sur_terrain_par_coordonnees(niveau, un_en_avant, TILE_EMPTY);
        break;
    }

    // On remplace la case un cran plus loin (que la case en face) par une case du bon type (caisse/caisse sur cible)
    switch(lecture_du_terrain_par_coordonnees(niveau, deux_en_avant)){
      case TILE_EMPTY: // Si la case deux pas en avant est vide, on place une caisse
        place_sur_terrain_par_coordonnees(niveau, deux_en_avant, TILE_CRATE);
        break;
      case TILE_TARGET: // Si la case deux pas en avant est une cible, on remplace par une caisse sur une sible
        place_sur_terrain_par_coordonnees(niveau, deux_en_avant, TILE_CRATE_ON_TARGET);
        break;
    }
  }
  
  // Si la case en face est libre
  if (case_libre_sur_terrain(niveau, un_en_avant->colonne, un_en_avant->ligne)){
    // On "déplace" le perso
    niveau->perso->colonne = un_en_avant->colonne;
    niveau->perso->ligne = un_en_avant->ligne;
    ajouter_niveau (etats_niveaux, niveau);
  } else {
    liberation_du_niveau(niveau);
  }

  free(un_en_avant);
  free(deux_en_avant);
}

bool case_libre_sur_terrain (niveau_t* niveau, int colonne, int ligne) {
  char car = lecture_du_terrain(niveau, colonne, ligne);

  // Si car = TILE_EMPTY ou TILE_TARGET
  // Si la case en question est vide ou est une cible
  switch (car){
    case TILE_EMPTY:
    case TILE_TARGET:
      return true;
    default:
      return false;
  }
}

// Vérifie si une caisse est présente aux coordonnées entrée en paramètres
bool caisse_sur_terrain (niveau_t* niveau, int colonne, int ligne){
  char car = lecture_du_terrain(niveau, colonne, ligne);

  // Si car = TILE_CRATE ou TILE_CRATE_ON_TARGET
  // Si la case en question est une caisse ou une caisse sur une cible
  switch (car){
    case TILE_CRATE:
    case TILE_CRATE_ON_TARGET:
      return true;
    default:
      return false;
  }
}

// Renvoie le nombre de caisses restantes
int nombre_de_caisse_restante_sur_terrain(niveau_t* niveau){
  int nombre_de_caisse = 0;

  // On boucle sur tous le niveau pour chercher le nombre de caisses qui ne sont pas sur une cible
  for(int indiceTerrain = 0; indiceTerrain < niveau->colonnes * niveau->lignes;indiceTerrain++){
    //On vérifie si le le tableau à l'indice indiceTerrain est une caisse
    //Si oui, on incrémente la valeur du nombre de caisse
    if(niveau->terrain[indiceTerrain] == TILE_CRATE){
      nombre_de_caisse++;
    }
  }

  return nombre_de_caisse;
}

void annuler_deplacement ()
{
  if (etats_niveaux->taille > 1) enlever_dernier_niveau (etats_niveaux);
}
