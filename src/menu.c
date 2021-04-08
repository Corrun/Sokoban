#include "main.h"

// Affiche le niveau de manière (très) brut.
void afficher_logo(){
   printf("\n                                      ▄▄                           \n ▄█▀▀▀█▄█        ▀███                ▄██                           \n▄██    ▀█          ██                 ██                           \n▀███▄     ▄██▀██▄  ██  ▄██▀  ▄██▀██▄  ██▄████▄  ▄█▀██▄ ▀████████▄  \n  ▀█████▄██▀   ▀██ ██ ▄█    ██▀   ▀██ ██    ▀████   ██   ██    ██  \n▄     ▀████     ██ ██▄██    ██     ██ ██     ██ ▄█████   ██    ██  \n██     ████▄   ▄██ ██ ▀██▄  ██▄   ▄██ ██▄   ▄████   ██   ██    ██  \n█▀█████▀  ▀█████▀▄████▄ ██▄▄ ▀█████▀  █▀█████▀ ▀████▀██▄████  ████▄\n"); 
}

// Permet de demander à l'utilisateur un int, pour ensuite choisir le niveau
int choix_du_niveau() {
    return menu_saisie_nombre("Choisis un niveau");
}

void afficher_regles(){
	int yMax, xMax; // Taille de la console en caractères
	effacer_ecran();
	int input = '\0';

	WINDOW* fenetre = nouvelle_fenetre();

	getmaxyx(stdscr, yMax, xMax); // Lire la taille de la console
		
	// Centrer la fenêtre
	centrer_fenetre(fenetre, 15 , 48 , yMax, xMax, 0, 0);  
	
	wclear(fenetre); // Raffraichi la fenêtre
	box(fenetre, 0, 0); // bordure de la fenêtre

	mvwprintw(fenetre, 0, 2, "Regles : ");
	mvwprintw(fenetre, 1, 1,"Règles classiques de Sokoban :");
	mvwprintw(fenetre, 2, 1,"Le joueur doit placer toutes les caisses (%c)", DISPLAY_TILE_CRATE);
	mvwprintw(fenetre, 3, 1,"sur toutes les cibles (%c)", DISPLAY_TILE_TARGET);
	mvwprintw(fenetre, 4, 1,"Mais attention !");
	mvwprintw(fenetre, 5, 1,"Un joueur est trop faible pour pousser");
	mvwprintw(fenetre, 6, 1,"2 caisses ... Ou même les tirer !");
	mvwprintw(fenetre,13, 1,"Pour retourner au menu, appuyer sur Q.");
	do
	{
		input = wgetch(fenetre);
	} while (input != 'q');
}

void afficher_credits(){
	int yMax, xMax; // Taille de la console en caractères
	effacer_ecran();
	int input = '\0';

	WINDOW* fenetre = nouvelle_fenetre();

	getmaxyx(stdscr, yMax, xMax); // Lire la taille de la console
		
	// Centrer la fenêtre
	centrer_fenetre(fenetre, 15 , 48 , yMax, xMax, 0, 0);  
	
	wclear(fenetre); // Raffraichi la fenêtre
	box(fenetre, 0, 0); // bordure de la fenêtre

	mvwprintw(fenetre, 0, 2, "Credits : ");
	mvwprintw(fenetre, 1, 2, "Un grand merci et bravo aux contributeurs");
	mvwprintw(fenetre, 2, 2, "du projets");
	mvwprintw(fenetre, 3, 2, "Je cite :");
	mvwprintw(fenetre, 4, 2, "ALMEIDA Néo");
	mvwprintw(fenetre, 5, 2, "ROUX Hugo");
	mvwprintw(fenetre, 6, 2, "VANOORENBERGHE Amaury");
	mvwprintw(fenetre, 8, 2, "Et aux librairies natives");
	mvwprintw(fenetre, 9, 2, "Et à la superbe librairie Ncurses !");
	mvwprintw(fenetre,13, 1,"Pour retourner au menu, appuyer sur Q.");
	do
	{
		input = wgetch(fenetre);
	} while (input != 'q');
}

/*void instruction_menu() {
    int leave;
    switch (instruction){
    case 1: //Jouer
        
        break;
    case 2: //Règles
        do{
            system("clear");
            afficher_regles();
            leave = scanf("%d",&leave);
        }while(leave == 'q' && leave == 'Q');
        break;        

     case 3: //Crédits
        do{
            system("clear");
            afficher_credits();
            leave = scanf("%d",&leave);
        }while(leave == 'q' && leave == 'Q');
        break;
    
     case 4: //Quitter
        printf("todo");
        break;

    default:
        return;
    }
}*/

int afficher_menu_principal() {
    char* entries[4];
	entries[0] = "Jouer";
	entries[1] = "Règles";
	entries[2] = "Credits";
	entries[3] = "Quitter";

	return menu_liste(15, 48, "Sokoban", entries, 4);
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
				mvwprintw(fenetre,  4 + (2 * num_element), 6, " ");
				wattroff(fenetre, COLOR_PAIR(COLOR_RED));
			}

			mvwprintw(fenetre,  4 + (2 * num_element), 8, elements[num_element]);

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
	int largeur_fenetre = strlen(titre);
	if (largeur_fenetre < 9) {
		largeur_fenetre = 9;
	}
	largeur_fenetre += 10;

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
	int largeur_fenetre = strlen(titre);
	if (largeur_fenetre < longueur_chaine_max) {
		largeur_fenetre = longueur_chaine_max;
	}
	largeur_fenetre += 10;

	int yMax, xMax; // Console size in chars

	WINDOW* fenetre = nouvelle_fenetre();	

	//char input_text[string_max_size] = { '\0' };
	char* texte_saisi = malloc(longueur_chaine_max * sizeof(char));
	texte_saisi[0] = '\0';

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
	
        return NULL;
    }
}