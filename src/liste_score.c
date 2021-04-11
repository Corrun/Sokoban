#include "main.h"

// Permet de créer un nouveau score
score_t* nouveau_score(void) {
	return malloc(sizeof(score_t));
}

// FIXME
void initialiser_score(score_t* score, int points, char* nom) {
	score->score = points;
	strncpy(score->nom, nom, 9);
}

// Libérer la totalité des scores
void liberer_score(score_t* score) {
	free(score);	
}

// Créée une nouvelle liste de scores
liste_score_t* nouvelle_liste_scores(void) {
	liste_score_t* scores = malloc(sizeof(liste_score_t));

	scores->memoire = malloc(SCORE_BUFFER_SIZE * sizeof(score_t*));
	
	for (int i = 0; i < SCORE_BUFFER_SIZE; ++i) {
		scores->memoire[i] = nouveau_score();
		initialiser_score(scores->memoire[i], 0, "");
	}

	scores->taille = 0;
	
	return scores;
}

void liberer_liste_scores (liste_score_t* scores) {
	for (int i = 0; i < SCORE_BUFFER_SIZE; ++i) {
		liberer_score(scores->memoire[i]);
	}

	free(scores->memoire);
	free(scores);
}

liste_score_t* lire_liste_scores (int numero_niveau) {
    char chemin_du_fichier[100];
    sprintf(chemin_du_fichier, "./niveau/score_multi_%d", numero_niveau);

    FILE* fichier = fopen(chemin_du_fichier, "r");

	if (!fichier) return NULL;

	liste_score_t* liste_score = nouvelle_liste_scores();


    int nombre_scores;
    fscanf(fichier, "%d", &nombre_scores);
    
	liste_score->taille = min(nombre_scores, SCORE_BUFFER_SIZE);

    for (int numero_score = 0; numero_score < nombre_scores; numero_score++) {
		fscanf(fichier, "%d %s", &(liste_score->memoire[numero_score]->score), liste_score->memoire[numero_score]->nom);
    }

    return liste_score;
}

// Enregistre une liste de scores dans un fichier niveau/score_multi_<nb>
// Où nb est numero_niveau
void enregistrer_liste_scores (liste_score_t* scores, int numero_niveau) {
	char nom_fichier[100];
	sprintf(nom_fichier, "./niveau/score_multi_%d", numero_niveau);
	
	FILE* fichier = fopen(nom_fichier, "w");

	if (!fichier) return;

	score_t* score;

	fprintf(fichier, "%d\n", scores->taille);

	for (int i = 0; i < scores->taille; ++i) {
		score = scores->memoire[i];
		fprintf(fichier, "%d %s\n", score->score, score->nom);
	}

	fclose(fichier);
}

// Retourne une vrai si
// le nombre de points passé en paramètre est un nouveau high score dans la liste
// ou si il reste au moins un emplacement libre dans la liste
bool inserable_dans_liste (liste_score_t* scores, int points) {
	return scores->taille == 0 || points < scores->memoire[scores->taille - 1]->score || scores->taille < SCORE_BUFFER_SIZE;
}

// Insère le score défini par points/nom dans la liste scores
// L'insertion n'a lieu que si le score est meilleur que le dernier
// Si un score pour le joueur nom existe déjà, on le met à jour à la place
void inserer_score_dans_liste (liste_score_t* scores, int points, char* nom) {
	if (!inserable_dans_liste(scores, points)) return;

	score_t* score;

	for (int numero_score = 0; numero_score < SCORE_BUFFER_SIZE; numero_score++) {
		score = scores->memoire[numero_score];
		
		if (numero_score < scores->taille) {
			if (strncmp(nom, score->nom, 8) == 0) {
				score->score = min(score->score, points);
				trier_liste_score(scores);
				return;
			}
		} else {
			initialiser_score(score, points, nom);
			scores->taille++;
			trier_liste_score(scores);
			return;
		}
	}
	initialiser_score(scores->memoire[scores->taille - 1], points, nom);
	trier_liste_score(scores);
}

// Trie les scores de la liste par ordre croissant
void trier_liste_score (liste_score_t* scores) {
	score_t** tab = scores->memoire;
	score_t* tmp;	

	for (int fixe = 0; fixe < scores->taille; ++fixe) {
		for (int curseur = fixe; curseur < scores->taille; ++curseur) {
			if (tab[curseur]->score < tab[fixe]->score) {
				tmp = tab[fixe];
				tab[fixe] = tab[curseur];
				tab[curseur] = tmp;
			}
		}
	}
}