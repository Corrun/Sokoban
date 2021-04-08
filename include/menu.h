#ifndef MENU_H_
#define MENU_H_

void afficher_logo();
int choix_du_niveau();
void afficher_regles();
void afficher_credits();
void instruction_menu(int instruction);

int afficher_menu_principal();
void afficher_liste_niveau_scoreboard();


int menu_liste(int hauteur, int largeur, char* titre, char** elements, int nb_elements);
int menu_saisie_nombre(char* titre);
char* menu_saisie_texte(char* titre, int longueur_chaine_max);

#endif // MENU_H_