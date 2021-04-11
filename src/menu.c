#include "main.h"

// Affiche le niveau de manière (très) brut.
void afficher_logo(void){
   printf(
	   "                                      ▄▄                           \n"
	   "  ▄█▀▀▀█▄█        ▀███                ▄██                          \n"
	   "▄██    ▀█          ██                 ██                           \n"
	   "▀███▄     ▄██▀██▄  ██  ▄██▀  ▄██▀██▄  ██▄████▄  ▄█▀██▄ ▀████████▄  \n"
	   "  ▀█████▄██▀   ▀██ ██ ▄█    ██▀   ▀██ ██    ▀████   ██   ██    ██  \n"
	   "▄     ▀████     ██ ██▄██    ██     ██ ██     ██ ▄█████   ██    ██  \n"
	   "██     ████▄   ▄██ ██ ▀██▄  ██▄   ▄██ ██▄   ▄████   ██   ██    ██  \n"
	   "█▀█████▀  ▀█████▀▄████▄ ██▄▄ ▀█████▀  █▀█████▀ ▀████▀██▄████  ████▄\n");  // 1017 chars > 552 symboles uniques

	   
}

// Permet de demander à l'utilisateur un entier, pour ensuite choisir le niveau
int choix_du_niveau(void) {
    return menu_saisie_nombre("Choisis un niveau");
}

// FIXME Refaire les règles ? (nouvelle_fenetre)
void afficher_regles(void){
	effacer_ecran();
	char regles_entiere[1000];
	sprintf(regles_entiere, "Règles classiques de Sokoban :\nLe joueur doit placer toutes les caisses (%c)\nsur toutes les cibles (%c)\nMais attention !\nUn joueur est trop faible pour pousser 2 caisses a la fois ...\nOu même les tirer !\n\nPour retourner au menu, appuyer sur entrée.", DISPLAY_TILE_CRATE, DISPLAY_TILE_TARGET);
	menu_message("Regles : ", regles_entiere, 50, 9, COLOR_GREEN, COLOR_WHITE);
}

// FIXME Refaire les credits ? (nouvelle_fenetre)
void afficher_credits(void) {
	effacer_ecran();
	char credits_entier[1000];
	sprintf(credits_entier, "Un grand merci et bravo aux contributeurs\ndu projets\nJe cite :\nALMEIDA Néo\nROUX Hugo\nVANOORENBERGHE Amaury\nEt aux librairies natives\nEt à la superbe librairie Ncurses !\n\nPour retourner au menu, appuyer sur entrée.\n");
	menu_message("Credits : ", credits_entier, 50, 10, COLOR_GREEN, COLOR_WHITE);
}

void afficher_liste_niveau_scoreboard(int numero_niveau) {
	FILE* fichier;
	char nom_fichier[100];

	sprintf(nom_fichier, "./niveau/niveau_%d", numero_niveau);
	fichier = fopen(nom_fichier, "r");
	if (!fichier) {
		menu_message("Erreur", "Le niveau specifie n'existe pas", 32, 1, COLOR_RED, COLOR_WHITE);
		return;
	}
	fclose(fichier);

	int yMax, xMax; // Taille de la console en caractères
	
	char titre[100];
	sprintf(titre, "Niveau %d - Meilleurs scores", numero_niveau);
	int largeur = max(40, strlen(titre));

	const int marge = 8;

	WINDOW* fenetre = nouvelle_fenetre();
	WINDOW* zone_texte = derwin(fenetre, SCORE_BUFFER_SIZE + 2, largeur, 2, marge / 2);

	liste_score_t* scores = lire_liste_scores(numero_niveau);

	do {
		getmaxyx(stdscr, yMax, xMax); // Lire la taille de la console
		
		effacer_ecran();
	
		centrer_fenetre(fenetre, 12, largeur + marge, yMax, xMax, 0, 0);

		wrefresh(fenetre);

		wattron(fenetre, COLOR_PAIR(COLOR_CYAN));
		box(fenetre, 0, 0);
		wattron(fenetre, A_STANDOUT);
		mvwprintw(fenetre, 0, 2, titre);
		wattroff(fenetre, A_STANDOUT);
		wattroff(fenetre, COLOR_PAIR(COLOR_CYAN));

		if (scores) {
			wattron(zone_texte, A_BOLD);
			mvwprintw(zone_texte, 0, 0, "Nom");
			mvwprintw(zone_texte, 0, largeur - 5, "Score");
			wattroff(zone_texte, A_BOLD);
			
			char texte[20];
			score_t* score;
			for (int i = 0; i < scores->taille; ++i) {
				score = scores->memoire[i];

				if (i == 0) {
					wattron(zone_texte, COLOR_PAIR(COLOR_YELLOW));
				}

				mvwprintw(zone_texte, 2 + i, 0, score->nom);

				sprintf(texte, "%d coups", score->score);
				mvwprintw(zone_texte, 2 + i, largeur - strlen(texte), texte);

				wattroff(zone_texte, COLOR_PAIR(COLOR_YELLOW));
			}
		} else {
			wattron(zone_texte, A_DIM);
			mvwprintw(zone_texte, 2, 0, "Aucun score disponible");
			wattroff(zone_texte, A_DIM);
		}
	} while (wgetch(fenetre) != KB_ENTER);

	if (scores) {
		liberer_liste_scores(scores);
	}
}

int afficher_menu_principal(void) {
    char* entries[5];
	entries[0] = "Jouer";
	entries[1] = "Règles";
	entries[2] = "Credits";
	entries[3] = "Leaderboards";
	entries[4] = "Quitter";

	return menu_liste(15, 52, "Sokoban", entries, 5);
}

int afficher_menu_quitter(void) {
    char* entries[2];
	entries[0] = "Non";
	entries[1] = "Oui";

	return menu_liste(9, 20, "Quitter ?", entries, 2);
}

// Affiche un menu composé d'une liste d'éléments
int menu_liste(int hauteur, int largeur, char* titre, char** elements, int nb_elements) {
	int yMax, xMax; // Taille de la console en caractères
	
	WINDOW* fenetre = nouvelle_fenetre(); // Nouvelle fenêtre

	int selection = 0; // Element sélectionné
	
	int input = '\0'; // Saisie

	while (true)
	{
		getmaxyx(stdscr, yMax, xMax); // Lire la taille de la console
		
		// Centrer la fenêtre
		centrer_fenetre(fenetre, hauteur, largeur, yMax, xMax, 0, 0);  

		effacer_ecran(); // Efface l'ecran
		
		wclear(fenetre); // Raffraichi la fenêtre
		box(fenetre, 0, 0); // bordure de la fenêtre

		mvwprintw(fenetre, 0, 2, titre); // Titre de la fenêtre

		for (int num_element = 0; num_element < nb_elements; ++num_element) {
			// Si l'élément actuel est sélectionné            
            if (selection == num_element) {
				wattron(fenetre, A_STANDOUT);
				wattron(fenetre, COLOR_PAIR(COLOR_RED));
				mvwprintw(fenetre,  3 + (2 * num_element), 5, " ");
				wattroff(fenetre, COLOR_PAIR(COLOR_RED));
			}

			mvwprintw(fenetre,  3 + (2 * num_element), 7, elements[num_element]);

			wattroff(fenetre, A_STANDOUT);
		}

		input = wgetch(fenetre); // Lecture de la saisie

		switch (input)
		{
			case KB_UP:
				selection--;
				selection = selection < 0 ? 0 : selection;
				break;
			case KB_DOWN:
				selection++;
				selection = selection >= nb_elements ? nb_elements - 1 : selection;
				break;
			case KB_ENTER:
				delwin(fenetre);
				return selection;
				break;
		}
	}

	return -1;
}

int menu_saisie_nombre(char* titre) {
	int largeur_fenetre = max(strlen(titre), 9) + 10;

	int yMax, xMax; // Console size in chars

	WINDOW* fenetre = nouvelle_fenetre();	

	char texte_saisi[9] = { '\0' };
	int longueur_texte = 0;

	int saisie = '\0';

	while (true)
	{
		longueur_texte = strlen(texte_saisi);

		getmaxyx(stdscr, yMax, xMax); // Read the console size
		
		centrer_fenetre(fenetre, 5, largeur_fenetre, yMax, xMax, 0, 0);  

		effacer_ecran();

		wclear(fenetre); // Rafraîchi la fenêtre
		box(fenetre, 0, 0); // Bordure de fenêtre

		mvwprintw(fenetre, 0, 2, titre); // Titre de la fenêtre

		wattron(fenetre, A_STANDOUT); // Surbrillance activée
		mvwprintw(fenetre, 2, 5, texte_saisi);
		if (longueur_texte < 9) {
			wattron(fenetre, COLOR_PAIR(COLOR_YELLOW));
			mvwprintw(fenetre, 2, 5 + longueur_texte, "_");
			wattroff(fenetre, COLOR_PAIR(COLOR_YELLOW));
		}
		wattroff(fenetre, A_STANDOUT); // Surbrillance désactivée

		saisie = wgetch(fenetre); // lecture saisie

		switch (saisie)
		{
			case KB_BACKSPACE:
				if (longueur_texte > 0) {
					texte_saisi[longueur_texte - 1] = '\0';
				}
				break;
			case KB_ENTER:
				if (longueur_texte == 0) break;

				delwin(fenetre);
				int numero = 10;
				sscanf(texte_saisi, "%d", &numero);
				return numero;
			default:
				if (longueur_texte < 9 && saisie >= '0' && saisie <= '9') {					
					texte_saisi[longueur_texte] = (char)saisie;
				}
				break;
		}
	}
	return -1;
}

char* menu_saisie_texte(char* titre, int longueur_chaine_max) {
	int largeur_fenetre = max(strlen(titre), longueur_chaine_max) + 10;

	int yMax, xMax; // Console size in chars

	WINDOW* fenetre = nouvelle_fenetre();	

	//char input_text[string_max_size] = { '\0' };
	char* texte_saisi = malloc(longueur_chaine_max * sizeof(char));
	memset(texte_saisi, '\0', longueur_chaine_max * sizeof(char));
	//texte_saisi[0] = '\0';

	int longueur_saisie = 0;

	int saisie = '\0';

	while (true) {
		longueur_saisie = strlen(texte_saisi);

		getmaxyx(stdscr, yMax, xMax); // Lecture de la taille de la console
		
		// Centrer fenetre
		centrer_fenetre(fenetre, 5, largeur_fenetre, yMax, xMax, 0, 0);  

		effacer_ecran(); // Efface l'ecran

		wclear(fenetre); // Raffraichi la fenêtre
		box(fenetre, 0, 0); // Bordure de la fenêtre

		mvwprintw(fenetre, 0, 2, titre); // Titre de la fenêtre

		wattron(fenetre, A_STANDOUT);
		mvwprintw(fenetre, 2, 5, texte_saisi);
		if (longueur_saisie < longueur_chaine_max) {
			mvwprintw(fenetre, 2, 5 + longueur_saisie, "_");
		}
		wattroff(fenetre, A_STANDOUT);

		saisie = wgetch(fenetre); // Wait for input

		switch (saisie) {
			case KB_BACKSPACE:
				if (longueur_saisie > 0) {
					texte_saisi[longueur_saisie - 1] = '\0';
				}
				break;
			case KB_ENTER:
				delwin(fenetre);
				return texte_saisi;
			default:; // Saisie texte
				if (longueur_saisie >= longueur_chaine_max) break;

				bool saisie_valide = false
				|| (saisie == ' ' || saisie == '_')
				|| (saisie >= '0' && saisie <= '9')
				|| (saisie >= 'a' && saisie <= 'z')
				|| (saisie >= 'A' && saisie <= 'Z');

				if (saisie_valide) {
					texte_saisi[longueur_saisie] = (char)saisie;
				}

				break;
		}
    }
    
	return NULL;
}

void menu_message (char* titre, char* message, int largeur, int hauteur, int couleur, int couleur_texte) {
	int yMax, xMax; // Taille de la console en caractères
	
	WINDOW* fenetre = nouvelle_fenetre(); // Nouvelle fenêtre
	WINDOW* zone_texte = derwin(fenetre, hauteur, largeur, 2, 2);

	do {
		getmaxyx(stdscr, yMax, xMax); // Lecture de la taille de la console

		centrer_fenetre(fenetre, hauteur + 4, largeur + 4, yMax, xMax, 0, 0);
		
		effacer_ecran();

		wattron(fenetre, COLOR_PAIR(couleur));
		wclear(fenetre);
		box(fenetre, 0, 0);
		
		wattron(fenetre, A_STANDOUT);
		mvwprintw(fenetre, 0, 2, titre);
		wattroff(fenetre, A_STANDOUT);
		wattroff(fenetre, COLOR_PAIR(couleur));
		
		
		wattron(zone_texte, COLOR_PAIR(couleur_texte));
		mvwprintw(zone_texte, 0, 0, message);
		wattroff(zone_texte, COLOR_PAIR(couleur_texte));

		wattroff(fenetre, couleur);
	} while (wgetch(fenetre) != KB_ENTER);

	delwin(zone_texte);
	delwin(fenetre);
}