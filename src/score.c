#include "main.h"

// Lecture du meilleur score depuis le fichier score_n 
// Où n est le numéro d'un niveau
int lecture_du_meilleur_score (int quel_niveau){
	FILE* fichier;
	char chemin_du_niveau[100];

 	sprintf(chemin_du_niveau,"./niveau/score_%d", quel_niveau);

	if ((fichier = fopen(chemin_du_niveau, "r"))) {
		// Le fichier a bien été ouvert
		int score_lu;
		int nombre_de_score = 0;
		int score_max = 0;
		int score_max_numero = 0;
        fscanf(fichier, "%d", &nombre_de_scores);

		for (int score_numero = 0; i < nombre_de_scores; score_numero++){
			fscanf(fichier, "%s %d", &score_lu); // ????
			if(score_lu > score_max){ // Besoin de recup le score d'une certaines manière
				*score = score_max;
				*score_max_numero = score_numero; // comme ça on a la ligne, ptetre faire +1
			}
		}
		fclose(fichier);

		return score_numero;
	} else {
		// Erreur de lecture (le fichier n'existe pas ?)
        
		return -1; // Retour d'une valeur d'erreur
	}
}

// Insertion du meilleur score dans le fichier score_nb où nb est le numéro du niveau. 
// (si le score obtenu en fin de partie est supérieur au meilleur score)
void ecriture_du_score (int quel_niveau, int score){
	FILE* fichier;
	char* player_name = nom_du_joueur();
	char chemin_du_niveau[100];
 	sprintf(chemin_du_niveau,"./niveau/score_%s %d",player_name ,quel_niveau);

	fichier = fopen(chemin_du_niveau, "w");

	fprintf(fichier, "%d", score);

	fclose(fichier);
}

// Demander le nom du joueur puis l'enregistre dans le tabeau des highscores
char* nom_du_joueur (void) {
    return menu_saisie_texte("Entrez votre nom", 8);
}
