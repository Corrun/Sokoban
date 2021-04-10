#ifndef CURSES_UTIL_H
#define CURSES_UTIL_H

void initialiser_ncurses();

void fermer_ncurses();

void initialiser_couleur(int couleur);

void calculer_centre(int hauteur, int largeur, int haut, int gauche, int* y, int* x);

void centrer_fenetre(WINDOW* fenetre, int hauteur_cible, int largeur_cible, int hauteur, int largeur, int haut, int gauche);

WINDOW* nouvelle_fenetre();

void effacer_ecran();

#endif // CURSES_UTIL_H