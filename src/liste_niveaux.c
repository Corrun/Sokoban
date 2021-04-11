#include "main.h"

// On utilise un tableau dynamique de niveau_t* pour stocker les
// etats du jeu au fur et a mesure que le joueur avance. Ainsi,
// etats_niveaux->memoire[0] est l'etat initial du jeu, et
// etats_niveaux->memoire[etats_niveaux->taille - 1] est l'etat courant.
// A chaque deplacement reussi, on ajoute une entree a la liste.
// A chaque annulation, on enleve le dernier element de la liste si il y en a plus qu'un.
liste_niveaux_t* etats_niveaux;

// Permet de créer une nouvelle liste de niveau, permettant par la suite d'utiliser le retour arrière
liste_niveaux_t* nouvelle_liste_niveaux(int taille) {
  liste_niveaux_t *resultat = malloc(sizeof(liste_niveaux_t));
  init_liste_niveaux (resultat, taille); //initialise la l
  return resultat;
}

// Permet d'initialiser les instances d'une liste de niveau, en fonction de la taille donnée
void init_liste_niveaux(liste_niveaux_t* liste, int taille) {
  liste->memoire = malloc (sizeof (niveau_t *) * taille);
  liste->taille = 0;
  liste->taille_memoire = taille;
}

// Permet de libérer la totalité des niveaux
void liberation_de_la_liste_niveaux(liste_niveaux_t* liste) {
  free(liste->memoire);
  liste->memoire = NULL;
  liste->taille = 0;
  liste->taille_memoire = 0;
}

// Permet d'agrandir la liste de niveau pour lui permettre d'accueillir un nouveau niveau (semblable à un tableau dynamique)
void agrandir_liste_de_niveaux(liste_niveaux_t *liste, int ajout) {
  if (ajout > 0) {
    niveau_t** nouveau = malloc(sizeof(niveau_t*) * (liste->taille_memoire + ajout));
    memcpy(nouveau, liste->memoire, sizeof(niveau_t*) * liste->taille);
    free(liste->memoire);
    liste->memoire = nouveau;
    liste->taille_memoire += ajout;
  }
}

// Permet d'ajouter un niveau à une liste de niveau passer en paramètre
void ajouter_niveau(liste_niveaux_t *liste, niveau_t* niveau) {
  if (liste->taille == liste->taille_memoire) {
    agrandir_liste_de_niveaux (liste, 10);
  }
  liste->memoire[liste->taille] = niveau;
  niveau->indice = liste->taille;
  liste->taille += 1;
}

// Permet de retirer le dernier niveau de la liste passée en paramètre (après une annulation de déplacement)
void enlever_dernier_niveau(liste_niveaux_t *liste) {
  if (liste->taille > 0) {
    liberation_du_niveau (haut_de_liste(etats_niveaux));
    liste->taille -= 1;
  }
}

// Permet de renvoyer le dernier élément de la liste, si la liste ne contient rien, cela renvoit NULL
niveau_t* haut_de_liste(liste_niveaux_t* liste) {
  if (liste->taille == 0) return NULL;
  return liste->memoire[liste->taille - 1];
}