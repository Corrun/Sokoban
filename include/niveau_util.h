#ifndef NIVEAU_UTIL_H_
#define NIVEAU_UTIL_H_

int coordonnees_vers_indice_terrain (niveau_t* niveau, int colonne, int ligne);

void indice_vers_coordonnees_niveau (niveau_t* niveau, int indice, int* colonne, int* ligne);

#endif // NIVEAU_UTIL_H_