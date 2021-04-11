#include "main.h"

// Permet de lancer un niveau, grâce a un numéro.
// Gère la totalité du jeu, en passant par son lancemant, son déroulement, sa fin (déchargement des niveaux)
void jouer_niveau(int numero_niveau) {
	int meilleur_score = lecture_du_score(numero_niveau);
	
	DEBUT_JEU:;

	// Attribution d'une nouvelle liste de niveaux (liste de taille 10)
	etats_niveaux = nouvelle_liste_niveaux (10);
	
	// Initialisation de niveau
	// Attribution de la lecture de niveau sur le numéro de niveau choisi précdemment
	niveau_t* niveau = lecture_du_niveau(numero_niveau);
	if (!niveau) return; //Si le niveau n'existe pas, on quitte la fonction (pas de jeu)

	// Initialisation de "scores" 
	// Attribution de la lecture de la liste des scores
	liste_score_t* scores = lire_liste_scores(numero_niveau);
	// Si il existe pas déjà un tableau de score 
	if (scores == NULL) {
		//Création d'un tableau de score pour le niveau
		scores = nouvelle_liste_scores();
	}
	
	// Ajout d'un niveau 
	ajouter_niveau (etats_niveaux, niveau);
	
	int saisie = 0;
	// On vérifie le niveua est terminé (si toutes les cases à remplir sont remplies)
	while (nombre_de_caisse_restante_sur_terrain(haut_de_liste(etats_niveaux)) > 0) {
		niveau = haut_de_liste(etats_niveaux);
		saisie = affichage_niveau_ncurses(niveau, numero_niveau);
		
		//On analyse la touche saisie par le joueur
		switch (saisie) {
			case LEAVE: 
				if (afficher_menu_quitter() == 1) { // Permet d'afficher un menu de confirmation avant de quitter
					goto FIN_JEU; // Si on entre dans le if, on est redirigé à la fin de la boucle. et on apparait au menu principale
				}
			case RESTART:
				if (afficher_menu_recommencer() == 1){ // Permet d'afficher un menu de confirmation avant de recommencer
					while (etats_niveaux->taille > 0) { // Permet libérer la totalité du tableau de niveau.
						enlever_dernier_niveau(etats_niveaux);
					}
				goto DEBUT_JEU;
				}
				break;
			case HELP:
				afficher_controles();
				break;
			case CANCEL:
				annuler_deplacement();
				break;
			default:
				deplacement(niveau, saisie);
				break;
		}
	}

	int nb_pas = etats_niveaux->taille - 1;
	
	//On vérifie si le score du joueur est
	//meilleur que le meilleur score actuel
	if (nb_pas < meilleur_score || meilleur_score < 0) {
		ecriture_du_score(numero_niveau, nb_pas);
	}

	//On vérifie si le score du joueur possède sa place dans le tableau des meilleurs scores
	if (inserable_dans_liste(scores, nb_pas)) { // Message 
		char message[100];

		// Message de meilleur score, il n'est pas affiché si il n'y avait aucun meilleur score auparavant
		// Le message s'affiche si 2 joueurs font un score égaux
		if(meilleur_score >= nb_pas){
			sprintf(message, "Vous avez terminé le niveau %i !!\nEt en seulement %d coups !!\nFélicitations !!", numero_niveau, nb_pas);
			menu_message("NOUVEAU MEILLEUR SCORE !!", message, 40, 3, COLOR_RED, COLOR_YELLOW);
		}else{ // Message de félicitation, quand un joueur a sa place dans le tableau des scores, mais pas à la première place.
			sprintf(message, "Bravo, vous avez termine le niveau %i!\nEt en seulement %d coups !!", numero_niveau, nb_pas);
			menu_message("Niveau fini", message, 40, 2, COLOR_GREEN, COLOR_YELLOW);
		}
		
		// On demande le nom du joueur, et on le place dans le tableau des scores 
		inserer_score_dans_liste(scores, nb_pas, nom_du_joueur());
		enregistrer_liste_scores(scores, numero_niveau);

		// Et on affiche le scoreboard après qu'il ai valider son nom
		afficher_liste_niveau_scoreboard(numero_niveau);
	} else { // Message s'affichant quand le joueur n'as pas sa place dans le tableau des scores
		char message[100];
		sprintf(message, "Bravo, vous avez termine le niveau %i!\nMais en trop de coups ...", numero_niveau);
		menu_message("Niveau fini", message, 40, 2, COLOR_GREEN, COLOR_WHITE);
	}
	
	FIN_JEU:;

	//On libère la mémoire que prend les scores
	liberer_liste_scores(scores);

	//Tant qu'on est pas de retour au premier état du terrain 
	//(où le joueur n'a pas encore effectuer de coup)
	while (etats_niveaux->taille > 0) {
		enlever_dernier_niveau(etats_niveaux); //Enlève le dernier niveau au tableau
	}
}