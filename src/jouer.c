#include "main.h"


void jouer (int numero_niveau) {
	DEBUT_JEU:;

	etats_niveaux = nouvelle_liste_niveaux (10);

	bool gagne = false;
	
	niveau_t* niveau = lecture_du_niveau(numero_niveau);

	if (!niveau) return;

	ajouter_niveau (etats_niveaux, niveau);
	
	int saisie = 0;
	while (!gagne) {
		niveau = haut_de_liste(etats_niveaux);
		saisie = affichage_niveau_ncurses(niveau);
		gagne = nombre_de_caisse_restante_sur_terrain(niveau) == 0;
		
		switch (saisie) {
			case LEAVE:
				//Foutre un msg de confirmation ??
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
	FIN_JEU:;

	while (etats_niveaux->taille > 0) {
		enlever_dernier_niveau(etats_niveaux);
	}


	// Gestion du score
}