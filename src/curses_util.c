#include "main.h"

// Démarrer le mode graphique de Ncurses
void initialiser_ncurses(void) {
	initscr(); // Initialisation de l'écran standard de Ncurses (stdscr)
	noecho(); // Ne pas écrire ce que l'utilisateur tape dans la saisie
	curs_set(false); // Cacher le curseur

	// Si le terminal ne supporte pâs les couleurs, on termine l'initialisation
	if (!has_colors()) {
		return;
	} else { // Sinon, on déclare les couleurs du mode graphique
		// Activation du mode couleur de ncurses
		start_color();

		// Déclaration des palettes de couleur
		initialiser_couleur(COLOR_RED); // Création de la couleur "rouge"
		initialiser_couleur(COLOR_GREEN); // Création de la couleur "vert"
		initialiser_couleur(COLOR_YELLOW); // Création de la couleur "jaune"
		initialiser_couleur(COLOR_BLUE); // Création de la couleur "bleu"
		initialiser_couleur(COLOR_MAGENTA); // Création de la couleur "magenta"
		initialiser_couleur(COLOR_CYAN); // Création de la couleur "cyan"
		initialiser_couleur(COLOR_WHITE); // Création de la couleur "blanc"
	}
}

// Désinitialisation de Ncurses
void fermer_ncurses(void) {
	endwin(); // Fermer toutes les fenêtres de ncurses actuellement ouvertes et quitter le mode "graphique"
}

// Initialisations des couleurs (pour Ncurses)
void initialiser_couleur(int couleur) {
	// La librairie ncurses gère les couleurs d'une façon particulière:
	// On doit déclarer une paire de couleurs de fond de texte avec un numéro de paire qui constituent une "palette"
	// Exemple: paire 1 = rouge en fond et blanc en couleur de texte.

	// Ici, on utilise un petit raccourci: Vu que les valeurs des couleurs de base du terminal vont de 0 à 7, on peut initialiser une paire avec ce même numéro
	// Exemple: 
	// Paire #1:
	// 	Couleur de texte: 1 (ROUGE)
	//	Couleur de fond: Noir
	init_pair(couleur, couleur, COLOR_BLACK);
}

// Calcule le centre d'une zone rectangulaire 
// Cette zone rectangulaire est définie comme suit :
/*
	  gauche (axe X)
		v
haut  > +-----------------+   ^
(axe Y)	|                 |   |
		|                 |   |
		|        X        |	  | hauteur (axe Y)
		|   x;y (centre)  |   |
		|                 |   |
		+-----------------+   V

		<---------------->
		  largeur (axe X)

	Les pointeurs x et y sont les valeurs de "retour" de la fonction
*/
void calculer_centre(int hauteur, int largeur, int haut, int gauche, int* y, int* x) {
	*y = haut + (hauteur / 2); // Attribution de la hauteur dans y 
	*x = gauche + (largeur / 2); // Attribution de la largeur dans x
}

// Centre une fenêtre dans une zone rectangulaire définie par les valeurs haut, gauche, hauteur et largeur
// La fenêtre aura la taille spécifiée par hauteur_cible et largeur_cible
// (voir explications de calculer_centre pour plus d'informations)
void centrer_fenetre(WINDOW* fenetre, int hauteur_cible, int largeur_cible, int hauteur, int largeur, int haut, int gauche) {
	//Initialisation des variabes "coordonnées"
	int y, x;

	calculer_centre(hauteur, largeur, haut, gauche, &y, &x); // calcule le centre de la fenêtre

	wresize(fenetre, hauteur_cible, largeur_cible); //Change la taille de la fenêtre
	mvwin(fenetre, y - (hauteur_cible / 2), x - (largeur_cible / 2)); //Change la position de la fenêtre
}

// Créer une nouvelle fenêtre de taille 0
WINDOW* nouvelle_fenetre(void) {
	WINDOW* fenetre = newwin(0, 0, 0, 0); // Nouvelle fenêtre de taille et position 0
	keypad(fenetre, true); // Ne pas attendre l'appui sur entrer pour recevoir la saisie
	return fenetre; //renvoi fenetre
}

// Efface l'écran et l'actualise
void effacer_ecran(void) {
	erase(); //Efface l'écran
	refresh(); //Actualise l'écran
}