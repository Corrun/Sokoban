#include "main.h"

// Affiche le niveau de manière (très) brut.
void afficher_logo(void){
   printf(
	   "  ▄▄                                                                \n"
	   " ▄██                            ▄█▀▀▀█▄█        ▀███                \n"
	   " ██                            ▄██    ▀█          ██                \n"
	   " ██▄████▄  ▄█▀██▄ ▀████████▄   ▀███▄     ▄██▀██▄  ██  ▄██▀  ▄██▀██▄ \n"
	   " ██    ▀████   ██   ██    ██     ▀█████▄██▀   ▀██ ██ ▄█    ██▀   ▀██\n"
	   " ██     ██ ▄█████   ██    ██   ▄     ▀████     ██ ██▄██    ██     ██\n"
	   " ██▄   ▄████   ██   ██    ██   ██     ████▄   ▄██ ██ ▀██▄  ██▄   ▄██\n"
	   " █▀█████▀ ▀████▀██▄████  ████▄ █▀█████▀  ▀█████▀▄████▄ ██▄▄ ▀█████▀ \n");  // 1017 chars > 552 symboles uniques   
}

// Permet de demander à l'utilisateur un entier, pour ensuite choisir le niveau
int choix_du_niveau(void) {
    return menu_saisie_nombre("Choisis un niveau");
}

// Permet d'afficher le menu des règles, que nous pouvons quitter avec la touche entrée
void afficher_regles(void) {
	char regles_entiere[1000];
	sprintf(regles_entiere, "Règles classiques du Bansoko :\nLe joueur doit placer toutes les caisses (%c)\nsur toutes les cibles (%c)\nMais attention !\nUn joueur est trop faible pour pousser 2 caisses a la fois ...\nOu même les tirer !\n\nPour quitter, appuyez sur ENTREE", DISPLAY_TILE_CRATE, DISPLAY_TILE_TARGET);
	menu_message("Regles : ", regles_entiere, 50, 9, COLOR_GREEN, COLOR_WHITE);
}

// Permet d'afficher le menu des crédits, que nous pouvons quitter avec la touche entrée
void afficher_credits(void) {
	char credits_entier[1000];
	sprintf(credits_entier, "Un grand merci et bravo aux contributeurs\ndu projets\nJe cite :\n  ALMEIDA Néo\n  ROUX Hugo\n  VANOORENBERGHE Amaury\nEt aux librairies natives\nEt à la superbe librairie Ncurses !\n\nPour quitter, appuyez sur ENTREE\n");
	menu_message("Credits : ", credits_entier, 50, 10, COLOR_BLUE, COLOR_WHITE);
}

// Permet d'afficher le menu des controles, que nous pouvons quitter avec la touche entrée
void afficher_controles(void) {
	char controles[1000];
	sprintf(controles, "Se deplacer: fleches / ZQSD\nAnnuler deplacement: %c\nRecommencer: %c\nQuitter: %c\n\nPour quitter, appuyez sur ENTREE", CANCEL, RESTART, LEAVE);
	menu_message("Controles : ", controles, 50, 6, COLOR_MAGENTA, COLOR_WHITE);
}

// Permet d'afficher une boite qui attend un chiffre, ce chiffre permet d'afficher les scores du niveau
// Le menu créer est quittable avec la touche entrée
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

		wrefresh(fenetre); // Raffraichissement de la fenêtre

		wattron(fenetre, COLOR_PAIR(COLOR_CYAN)); // Texte en cyan activé
		box(fenetre, 0, 0); // Dessine une bordure
		wattron(fenetre, A_STANDOUT); // Texte en gras activé
		mvwprintw(fenetre, 0, 2, titre);
		wattroff(fenetre, A_STANDOUT); // Texte en gras désactivé
		wattroff(fenetre, COLOR_PAIR(COLOR_CYAN)); // Texte en cyan désactivé
 
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
			wattron(zone_texte, A_DIM); // Texte sombre activé
			mvwprintw(zone_texte, 2, 0, "Aucun score disponible");
			wattroff(zone_texte, A_DIM); // Texte sombre désactivé
		}

		wattron(fenetre, A_DIM); // Texte sombre activé
		mvwprintw(fenetre, 10, 4, "Pour quitter, appuyer sur ENTREE");
		wattroff(fenetre, A_DIM); // Texte sombre désactivé
	} while (wgetch(fenetre) != KB_ENTER);

	if (scores) {
		liberer_liste_scores(scores);
	}
}

// Permet d'afficher le menu principal, celui-ci peut être navigué grâce aux flêches directionnelles (haut et bas)
int afficher_menu_principal(void) {
    char* entries[6];
	entries[0] = "Jouer";
	entries[1] = "Règles";
	entries[2] = "Controles";
	entries[3] = "Credits";
	entries[4] = "Leaderboards";
	entries[5] = "Quitter";

	return menu_liste(17, 51, "Bansoko", entries, 6);
}

// Afficher un menu de confirmation (oui/non) navigable avec les flèches haut/bas
int afficher_menu_quitter(void) {
    char* entries[2];
	entries[0] = "Non";
	entries[1] = "Oui";

	return menu_liste(9, 20, "Quitter ?", entries, 2);
}

// Afficher un menu de confirmation (oui/non) navigable avec les flèches haut/bas, permettant de recommencer le niveau
int afficher_menu_recommencer(void) {
    char* entries[2];
	entries[0] = "Non";
	entries[1] = "Oui";

	return menu_liste(9, 20, "Recommencer ?", entries, 2);
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
				wattron(fenetre, A_STANDOUT); // Texte gras activé
				wattron(fenetre, COLOR_PAIR(COLOR_RED)); // Texte rouge activé
				mvwprintw(fenetre,  3 + (2 * num_element), 5, " "); // On affiche un espace (la barre rouge de l'élément sélectionné :D)
				wattroff(fenetre, COLOR_PAIR(COLOR_RED)); // Texte rouge désactivé
			}

			//Affiche les multiples choix du menu
			mvwprintw(fenetre,  3 + (2 * num_element), 7, elements[num_element]);
			
			wattroff(fenetre, A_STANDOUT); // Texte gras désactivé
		}

		input = wgetch(fenetre); // Lecture de la saisie

		switch (input) // Permet de naviguer dans le menu
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

// Affiche un menu permettant d'entrer (seulement) des nombres, que l'ont peut valider avec entrée, 9 chiffres sont acceptés. On peut les supprimer si besoin.
int menu_saisie_nombre(char* titre) {
	int largeur_fenetre = max(strlen(titre), 9) + 10;

	int yMax, xMax; // Console size in chars

	WINDOW* fenetre = nouvelle_fenetre();	

	char texte_saisi[9] = { '\0' };
	memset(texte_saisi, '\0', 9 * sizeof(char));
	
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
			case KB_BACKSPACE: // Effacer caractère
				if (longueur_texte > 0) {
					texte_saisi[longueur_texte - 1] = '\0';
				}
				break;
			case KB_ENTER: // Valider saisie (seulement si saisie non vide)
				if (longueur_texte == 0) break;

				delwin(fenetre);
				int numero = 10;
				sscanf(texte_saisi, "%d", &numero);
				return numero;
			default:
				// On accepte que les chiffres
				if (longueur_texte < 9 && saisie >= '0' && saisie <= '9') {					
					texte_saisi[longueur_texte] = (char)saisie;
				}
				break;
		}
	}
	return -1;
}

// Affiche un menu permettant d'entrer des chiffres, mais aussi des lettres, et des '_', que l'ont peut valider avec entrée, 8 caractère sont acceptés. On peut les supprimer si besoin.
char* menu_saisie_texte(char* titre, int longueur_chaine_max) {
	int largeur_fenetre = max(strlen(titre), longueur_chaine_max) + 10;

	int yMax, xMax; // Console size in chars

	WINDOW* fenetre = nouvelle_fenetre();	

	char* texte_saisi = malloc(longueur_chaine_max * sizeof(char));
	memset(texte_saisi, '\0', longueur_chaine_max * sizeof(char));

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

		wattron(fenetre, A_STANDOUT); // Texte gras activé
		mvwprintw(fenetre, 2, 5, texte_saisi);
		if (longueur_saisie < longueur_chaine_max) {
			mvwprintw(fenetre, 2, 5 + longueur_saisie, "_");
		}
		wattroff(fenetre, A_STANDOUT); // Texte gras désactivé

		saisie = wgetch(fenetre); // Lire la saisie

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
				// Ne pas autoriser la saisie si la longueur de chaine est déjà au maximum
				if (longueur_saisie >= longueur_chaine_max) break;

				// N'autoriser que les lettres (minuscules/majuscules), les chiffres, espaces et ttirets bas (underscores)
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

// Affiche une fenêtre qui recouvre la fenêtre actuel, grâce à ses nombreux paramêtres, elle est customisable. On peut la quitter avec la touche entrée
void menu_message (char* titre, char* message, int largeur, int hauteur, int couleur, int couleur_texte) {
	int yMax, xMax; // Taille de la console en caractères
	
	WINDOW* fenetre = nouvelle_fenetre(); // Nouvelle fenêtre
	WINDOW* zone_texte = derwin(fenetre, hauteur, largeur, 2, 2);

	do {
		getmaxyx(stdscr, yMax, xMax); // Lecture de la taille de la console

		centrer_fenetre(fenetre, hauteur + 4, largeur + 4, yMax, xMax, 0, 0);
		
		effacer_ecran();

		wattron(fenetre, COLOR_PAIR(couleur)); // Sélection de la couleur de fond
		wclear(fenetre);
		box(fenetre, 0, 0);
		
		wattron(fenetre, A_STANDOUT); // Texte gras activé
		mvwprintw(fenetre, 0, 2, titre);
		wattroff(fenetre, A_STANDOUT); // Texte gras désactivé
		wattroff(fenetre, COLOR_PAIR(couleur)); // Désélection de la couleur de fond
		
		wattron(zone_texte, COLOR_PAIR(couleur_texte)); // Sélection de la couleur de texte
		mvwprintw(zone_texte, 0, 0, message);
		wattroff(zone_texte, COLOR_PAIR(couleur_texte)); // Désélection de la couleur de texte
	} while (wgetch(fenetre) != KB_ENTER);

	delwin(zone_texte);
	delwin(fenetre);
}