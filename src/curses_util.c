#include "main.h"

// Démarrer le mode graphique de Ncurses
void initialiser_ncurses(void) {
	initscr(); // Initialisation de Ncurses
	noecho(); // Ne pas écrire ce que l'utilisateur écrit
	curs_set(false); // Cacher le curseur

	// Si les couleurs ne sont pas encore initialisées, on les initialise
	if (!has_colors()) {
		return;
	} else {
		// Création des palettes de couleurs
		start_color();
		initialiser_couleur(COLOR_RED);
		initialiser_couleur(COLOR_GREEN);
		initialiser_couleur(COLOR_YELLOW);
		initialiser_couleur(COLOR_BLUE);
		initialiser_couleur(COLOR_MAGENTA);
		initialiser_couleur(COLOR_CYAN);
		initialiser_couleur(COLOR_WHITE);
	}
}

// Désinitialisation de Ncurses
void fermer_ncurses(void) {
	endwin(); // Fermer toutes les fenêtres de ncurses
}

void initialiser_couleur(int couleur) {
	init_pair(couleur, couleur, COLOR_BLACK);
}

// Calcule le centre d'une zone rectangulaire définie par les valeurs haut, gauche, hauteur et largeur
// Le centre calculé sera stocké dans les valeurs x et y
void calculer_centre(int hauteur, int largeur, int haut, int gauche, int* y, int* x){
	*y = haut + (hauteur / 2);
	*x = gauche + (largeur / 2);
}

// Centre une fenêtre dans une zone rectangulaire définie par les valeurs haut, gauche, hauteur et largeur
// La fenêtre aura la taille spécifiée par hauteur_cible et largeur_cible
void centrer_fenetre(WINDOW* fenetre, int hauteur_cible, int largeur_cible, int hauteur, int largeur, int haut, int gauche){
	int y, x;

	calculer_centre(hauteur, largeur, haut, gauche, &y, &x);

	wresize(fenetre, hauteur_cible, largeur_cible);
	mvwin(fenetre, y - (hauteur_cible / 2), x - (largeur_cible / 2));
}

// Créée une nouvelle fenêtre de taille 0
WINDOW* nouvelle_fenetre(void) {
	WINDOW* fenetre = newwin(0, 0, 0, 0); // Nouvelle fenêtre de taille et position 0
	keypad(fenetre, true); // Ne pas attendre l'appui sur entrer pour recevoir la saisie
	return fenetre;
}

// Efface l'écran et l'actualise
void effacer_ecran(void) {
	erase(); 
	refresh();
}