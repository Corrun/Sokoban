#ifndef LISTE_NIVEAUX_H_
#define LISTE_NIVEAUX_H_

extern liste_niveaux_t* etats_niveaux;

liste_niveaux_t *nouvelle_liste_niveaux(int taille);

void init_liste_niveaux(liste_niveaux_t* liste, int taille);

void liberation_de_la_liste_niveaux(liste_niveaux_t* liste);

void ajouter_niveau(liste_niveaux_t* liste, niveau_t* niveau);

void enlever_dernier_niveau(liste_niveaux_t* liste);

niveau_t* haut_de_liste(liste_niveaux_t* liste);

#endif // LISTE_NIVEAUX_H_