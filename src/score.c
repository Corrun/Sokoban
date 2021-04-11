#include "main.h"

// Lecture du meilleur score depuis le fichier score_nb 
// Où nb est le numéro d'un niveau
int lecture_du_score(int quel_niveau) {
	FILE* fichier;

	char nom_fichier[100];

 	sprintf(nom_fichier,"./niveau/score_%d", quel_niveau);

	if ((fichier = fopen(nom_fichier, "r"))) {
		// Le fichier a bien été ouvert
		int score;

        fscanf(fichier, "%d", &score);

		fclose(fichier);

		return score;
	} else {
		ecriture_du_score(quel_niveau, -1);
		// Erreur de lecture (le fichier n'existe pas ?)
		return -1; // Retour d'une valeur d'erreur
	}
}


// Insertion du meilleur score dans le fichier score_nb où nb est le numéro du niveau. 
// (si le score obtenu en fin de partie est supérieur au meilleur score)
void ecriture_du_score(int quel_niveau, int score){
	FILE* fichier;
	char nom_fichier[100];
	sprintf(nom_fichier, "./niveau/score_%d", quel_niveau);

	fichier = fopen(nom_fichier, "w");
	
	fprintf(fichier, "%d", score);
	
	fclose(fichier);
}

// Demander le nom du joueur puis l'enregistre dans le tabeau des highscores
char* nom_du_joueur(void) {
    return menu_saisie_texte("Entrez votre nom", 8);
}