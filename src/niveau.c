#include "main.h"

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

// Affiche un niveau et renvoie la saisie de l'utilisateur
// Note : cette fonction récupère les inputs de l'utilisateur
// ATTENTION: Cette fonction se charge de l'affichage ET de la lecture de la saisie clavier
char affichage_niveau_ncurses (niveau_t* niveau, int numero_niveau) {
  int yMax, xMax; // Taille de la console en caractères
	
  int meilleur_score = lecture_du_score(numero_niveau);
  char info[100];

  int largeur = 0; // Largeur de la fenetre (création d'une variable car taille non constante)

	WINDOW* fenetre = nouvelle_fenetre(); // Nouvelle fenêtre
  
  int saisie = '\0';

  while (true) {
    getmaxyx(stdscr, yMax, xMax); // Lire la taille de la console
		
    // Création du titre de la fenêtre:
    // Si un high score existe déjà:
    if (meilleur_score >= 0) {
      sprintf(info, "Niveau %i | Record: %i coups | %i coups", numero_niveau, meilleur_score, etats_niveaux->taille - 1);
    } else { // Sinon, si le niveau n'a pas de high score
      sprintf(info, "Niveau %i | Record: aucun | %i coups", numero_niveau, etats_niveaux->taille - 1);
    }
    
    // Calcul de la largeur idéale de la fenêtre
		largeur = 2 + max(niveau->colonnes, strlen(info));
    
    // Centrer la fenêtre
		centrer_fenetre(fenetre, niveau->lignes + 2, largeur + 2, yMax, xMax, 0, 0);  

		effacer_ecran(); // Efface l'ecran
		
		box(fenetre, 0, 0); // Bordure de la fenêtre

    // Permet de calculer le décalage horizontal du niveau pour le centrer dans la fenêtre
    int decalage = (largeur - niveau->colonnes) / 2;

    // Affichage du terrain
    for (int ligne = 0; ligne < niveau->lignes; ++ligne) {
      for (int colonne = 0; colonne < niveau->colonnes; ++colonne) {
        //char case_terrain = lecture_du_terrain(niveau, colonne, ligne);
        char case_affichee = '\0';

        int attribut = modification_affichage_niveau(niveau, colonne, ligne, &case_affichee);

        wattron(fenetre, attribut);
        
        mvwaddch(fenetre, ligne + 1, colonne + 1 + decalage, case_affichee);
        wattroff(fenetre, attribut);
        wrefresh(fenetre);
      }
    }
    
    //sprintf("Coups %c", niveau->nb_de_pas);
    wattron(fenetre, A_STANDOUT);
    mvwprintw(fenetre, 0, 2, info); // Titre de la fenetre (à changer pour afficher le niveau actuel)

    //mvwprintw(fenetre, niveau->lignes+1, niveau->colonnes-5, nb_coups); // Nombre de pas (actuellement à 0 vu que c'est l'initialisation du niveau)
    wattroff(fenetre, A_STANDOUT);
    mvwprintw(fenetre, niveau->lignes + 1, 2, "[ F1 ou h : Afficher controles ]");

    saisie = majuscule_en_minuscule(wgetch(fenetre));

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
      case HELP:
        return (char)saisie;
      case KB_F1:
        return HELP;
    }
  }
}

// Fonction en charge de lire une case de terrain et de retourner le bon symbole à afficher via le pointeur symbole
// Cette fonction renvoie un int correspondant à un code de mise en forme NCurses (couleur, gras, ...)
int modification_affichage_niveau (niveau_t* niveau, int x, int y, char* symbole) {
  char case_terrain = lecture_du_terrain(niveau, x, y);

  // COmme on n'enregistre pas le joueur comme position dans le terrain
  // mais via le point_t niveau-> perso, on doit procéder à des vérifications avant l'affichage
  // Si la case demandée est celle du joueur...
  if (x == niveau->perso->colonne && y == niveau->perso->ligne) {
    switch (case_terrain) {
      case TILE_EMPTY: // Si la case est vide
        case_terrain = TILE_PLAYER; // On dit que la case est un joueur
        break;
      case TILE_TARGET: // Si la case est une cible
        case_terrain = TILE_PLAYER_ON_TARGET; // La case affichee sera un joueur sur une cible
        break;
    }
  }

  // Switch sur le type de case (lu depuis le terrain) 
  // pour remplacer par le caractèrre qui sera affiché
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
      return COLOR_PAIR(COLOR_YELLOW);
    case TILE_PLAYER:
      *symbole = DISPLAY_TILE_PLAYER;
      return A_BOLD | COLOR_PAIR(COLOR_GREEN);
    case TILE_PLAYER_ON_TARGET:
      *symbole = DISPLAY_TILE_PLAYER_ON_TARGET;
      return A_BOLD | COLOR_PAIR(COLOR_GREEN);
    default:
      *symbole = case_terrain;
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

// Lire un niveau depuis un fichier (dans niveau/)
niveau_t* lecture_du_niveau (int numero_niveau){
  FILE* fichier;
  char chemin_du_niveau[100];

  sprintf(chemin_du_niveau,"./niveau/niveau_%d", numero_niveau);
  fichier = fopen(chemin_du_niveau, "r"); // On ouvre le fichier en lecture
  
  // Gestion des erreurs...
  if (!fichier) {
    menu_message("Fichier introuvable", "Le niveau n'existe pas", 30, 1, COLOR_RED, COLOR_WHITE);
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
      // On place le caractère lu sur le terrain puis on incrémente
      // l'adresse/l'indice d'écriture
      place_sur_terrain(niveau, colonne, ligne, car);
      analyser_case_niveau(niveau, indice_terrain);

      ++indice_terrain;
    }

    car = fgetc(fichier); // On récupère le prochain caractère du fichier
  }
  
  fclose(fichier); // On oublie pas de fermer le fichier :D

  // Gestion des erreurs...
  if (!niveau->perso) {
    menu_message("Personnage introuvable", "Le niveau ne contient pas d'emplacement de depart ('@')", 30, 3, COLOR_YELLOW, COLOR_WHITE);
    return NULL;
  }

  // Gestion des erreurs...
  if (nombre_de_caisse_restante_sur_terrain(niveau) != nombre_cible_sur_terrain(niveau)) {
    menu_message("Erreur de validation", "Le niveau ne contient pas assez de cibles (.)\nPour pouvoir placer toutes les caisses ($)", 48, 2, COLOR_YELLOW, COLOR_WHITE);
    return NULL;
  }

  return niveau;
}

// Calcule le nombrede cibles sans caisses sur le terrain
int nombre_cible_sur_terrain(niveau_t* niveau){
  int nombre_de_cibles = 0;
  for(int indiceTerrain = 0; indiceTerrain < niveau->colonnes * niveau->lignes;indiceTerrain++){
      if(niveau->terrain[indiceTerrain] == TILE_TARGET){
        nombre_de_cibles++;
      }
    }
  return nombre_de_cibles;
}

// Analyse la case à un indice donné et modifie les propriétés de niveau en conséquences
// Exemple: si la case lue est un @, on modifie la propriété niveau->perso puis on replace par une case sol
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

// La case est-elle navigable ? (le joueur/une caisse peut-il aller dessus ?)
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

// Renvoie le nombre de caisses restantes (qui ne sont pas sur une cible)
int nombre_de_caisse_restante_sur_terrain(niveau_t* niveau){
  int nombre_de_caisse = 0;

  // On boucle sur tous le niveau pour chercher le nombre de caisses qui ne sont pas sur une cible
  for(int indiceTerrain = 0; indiceTerrain < niveau->colonnes * niveau->lignes;indiceTerrain++){
    //On vérifie si le le tableau à l'indice indiceTerrain est une caisse
    //Si oui, on incrémente la valeur du nombre de caisse
    if(niveau->terrain[indiceTerrain] == TILE_CRATE) {
      nombre_de_caisse++;
    }
  }

  return nombre_de_caisse;
}