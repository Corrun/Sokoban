#ifndef LISTE_SCORE_H_
#define LISTE_SCORE_H_

score_t* nouveau_score(void);

void initialiser_score(score_t* score, int points, char* nom);

void liberer_score(score_t* score);

liste_score_t* nouvelle_liste_scores(void);

void liberer_liste_scores(liste_score_t* scores);

liste_score_t* lire_liste_scores(int numero_niveau);

void enregistrer_liste_scores(liste_score_t* scores, int numero_niveau);

bool inserable_dans_liste(liste_score_t* scores, int points);

void inserer_score_dans_liste(liste_score_t* scores, int points, char* nom);

void trier_liste_score(liste_score_t* scores);

#endif // LISTE_SCORE_H_