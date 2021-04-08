#include "main.h"


void jouer (int numero_niveau) {
	DEBUT_JEU:;
	bool gagne = false;
	niveau_t* niveau = lecture_du_niveau(numero_niveau);

	int saisie = 0;
	do {
		saisie = affichage_niveau_ncurses(niveau);
		
		switch (saisie) {
			case LEAVE:
				//Foutre un msg de confirmation ??
				goto FIN_JEU;
			case RESTART:
				liberation_du_niveau(niveau);
				goto DEBUT_JEU;
			case CANCEL:
				annuler_deplacement(niveau);
				break;
			default:
				deplacement(niveau, saisie);
				break;
		}
		
		gagne = nombre_de_caisse_restante_sur_terrain(niveau) == 0;
	} while(!gagne);
	FIN_JEU:;


	liberation_du_niveau(niveau);


	// Gestion du score
}