#include "main.h"

// Permet de lancer un niveau, grâce a un numéro.
void jouer_niveau(int numero_niveau) {
	int meilleur_score = lecture_du_score(numero_niveau);
	
	DEBUT_JEU:;

	etats_niveaux = nouvelle_liste_niveaux (10);

	bool gagne = false;
	
	niveau_t* niveau = lecture_du_niveau(numero_niveau);
	if (!niveau) return;

	liste_score_t* scores = lire_liste_scores(numero_niveau);
	if (!scores) {
		scores = nouvelle_liste_scores();
	}
	
	ajouter_niveau (etats_niveaux, niveau);
	
	int saisie = 0;
	while (!gagne) {
		niveau = haut_de_liste(etats_niveaux);
		saisie = affichage_niveau_ncurses(niveau, numero_niveau);
		gagne = nombre_de_caisse_restante_sur_terrain(niveau) == 0;
		
		switch (saisie) {
			case LEAVE:
				// FIXME: Foutre un msg de confirmation ??
				goto FIN_JEU;
			case RESTART:
				while (etats_niveaux->taille > 0) {
					enlever_dernier_niveau(etats_niveaux);
				}
				goto DEBUT_JEU;
			case CANCEL:
				annuler_deplacement();
				break;
			default:
				deplacement(niveau, saisie);
				break;
		}
	}

	int nb_pas = etats_niveaux->taille - 2;

	if (meilleur_score >= 0 && nb_pas < meilleur_score) {
		ecriture_du_score(numero_niveau, nb_pas);
	}

	if (inserable_dans_liste(scores, nb_pas)) {
		inserer_score_dans_liste(scores, nb_pas, nom_du_joueur());
		enregistrer_liste_scores(scores, numero_niveau);
	}
	FIN_JEU:;

	liberer_liste_scores(scores);

	while (etats_niveaux->taille > 0) {
		enlever_dernier_niveau(etats_niveaux);
	}
}