#ifndef MENU_H_
#define MENU_H_

void afficher_logo ();

int choix_du_niveau ();

void afficher_regles ();

void afficher_credits ();

void instruction_menu (int instruction);


int afficher_menu_principal ();

int afficher_menu_quitter ();

void afficher_liste_niveau_scoreboard (int numero_niveau);

int menu_liste (int hauteur, int largeur, char* titre, char** elements, int nb_elements);

int menu_saisie_nombre (char* titre);

char* menu_saisie_texte (char* titre, int longueur_chaine_max);

void menu_message (char* titre, char* message, int largeur, int hauteur, int couleur, int couleur_texte);

#endif // MENU_H_