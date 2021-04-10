#ifndef NIVEAU_H_
#define NIVEAU_H_

niveau_t* nouveau_niveau (int nb_colonnes, int nb_lignes);

void liberation_du_niveau (niveau_t* niveau);

char affichage_niveau_ncurses (niveau_t* niveau, int numero_niveau);

int modification_affichage_niveau (niveau_t* niveau, int x, int y, char* symbole);

void affichage_niveau (niveau_t* niveau);

niveau_t* lecture_du_niveau (int quel_niveau);

void analyser_case_niveau (niveau_t* niveau, int indice);

bool case_libre_sur_terrain (niveau_t* niveau, int colonne, int ligne);

bool caisse_sur_terrain (niveau_t* niveau, int colonne, int ligne);

int nombre_de_caisse_restante_sur_terrain (niveau_t* niveau);

niveau_t* copier_niveau (niveau_t *source);

#endif // NIVEAU_H_

