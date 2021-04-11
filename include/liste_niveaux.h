#ifndef LISTE_NIVEAUX_H_
#define LISTE_NIVEAUX_H_

/*
 * On utilise un tableau dynamique de niveau_t* pour stocker les
 * etats du jeu au fur et a mesure que le joueur avance. Ainsi,
 * etats_niveaux->memoire[0] est l'etat initial du jeu, et
 * etats_niveaux->memoire[etats_niveaux->taille - 1] est l'etat courant.
 * A chaque deplacement reussi, on ajoute une entree a la liste.
 * A chaque annulation, on enleve le dernier element de la liste si il y en a plus qu'un.
 */
extern liste_niveaux_t* etats_niveaux;

liste_niveaux_t *nouvelle_liste_niveaux(int taille);

void init_liste_niveaux(liste_niveaux_t* liste, int taille);

void liberation_de_la_liste_niveaux(liste_niveaux_t* liste);

void ajouter_niveau(liste_niveaux_t* liste, niveau_t* niveau);

void enlever_dernier_niveau(liste_niveaux_t* liste);

niveau_t* haut_de_liste(liste_niveaux_t* liste);

#endif // LISTE_NIVEAUX_H_