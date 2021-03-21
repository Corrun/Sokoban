#ifndef PERSO_T_H_
#define PERSO_T_H_

char entree_du_joueur (void); // FIXME: Déplacer dans un fichier séparé (cf: input.h)
perso_t* nouveau_personnage (void);
void initialise_personnage (perso_t* personnage, int colonne, int ligne);
perso_t* trouver_perso (niveau_t* niveau);

#endif // PERSO_T_H_