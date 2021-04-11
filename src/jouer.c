#include "main.h"

// Permet de lancer un niveau, grâce a un numéro.
void jouer_niveau(int numero_niveau) {
	int meilleur_score = lecture_du_score(numero_niveau);
	
	DEBUT_JEU:;

	etats_niveaux = nouvelle_liste_niveaux (10);
	
	niveau_t* niveau = lecture_du_niveau(numero_niveau);
	if (!niveau) return;

	liste_score_t* scores = lire_liste_scores(numero_niveau);
	if (scores == NULL) {
		scores = nouvelle_liste_scores();
	}
	
	ajouter_niveau (etats_niveaux, niveau);
	
	int saisie = 0;
	while (nombre_de_caisse_restante_sur_terrain(haut_de_liste(etats_niveaux)) > 0) {
		niveau = haut_de_liste(etats_niveaux);
		saisie = affichage_niveau_ncurses(niveau, numero_niveau);
		
		switch (saisie) {
			case LEAVE:
				if (afficher_menu_quitter() == 1) {
					goto FIN_JEU;
				}
			case RESTART:
				while (etats_niveaux->taille > 0) {
					enlever_dernier_niveau(etats_niveaux);
				}
				goto DEBUT_JEU;
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

	int nb_pas = etats_niveaux->taille - 2;
	
	if (nb_pas < meilleur_score || meilleur_score < 0) {
		ecriture_du_score(numero_niveau, nb_pas);
	}

	if (inserable_dans_liste(scores, nb_pas)) {
		inserer_score_dans_liste(scores, nb_pas, nom_du_joueur());
		enregistrer_liste_scores(scores, numero_niveau);
		afficher_liste_niveau_scoreboard(numero_niveau);
	} else {
		char message[50];
		sprintf(message, "Bravo, vous avez termine le niveau %i!", numero_niveau);
		menu_message("Niveau fini", message, 40, 1, COLOR_GREEN, COLOR_WHITE);
	}
	
	FIN_JEU:;

	liberer_liste_scores(scores);

	while (etats_niveaux->taille > 0) {
		enlever_dernier_niveau(etats_niveaux);
	}
}