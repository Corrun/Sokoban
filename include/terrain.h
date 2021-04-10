#ifndef TERRAIN_H_
#define TERRAIN_H_

void initialise_terrain (niveau_t* niveau);

void place_sur_terrain (niveau_t* niveau, int colonne, int ligne, char car);

void place_sur_terrain_par_coordonnees (niveau_t* niveau, point_t* coord, char car);

char lecture_du_terrain (niveau_t* niveau, int colonne, int ligne);

char lecture_du_terrain_par_coordonnees (niveau_t* niveau, point_t* coord);

int taille_tableau_terrain (niveau_t* niveau);

#endif // TERRAIN_H_