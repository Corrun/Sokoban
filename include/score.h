#ifndef SCORE_H_
#define SCORE_H_

/*
// Lire l'entièreté d'un fichier
FILE *file = fopen (filename, "r");
if (!file) return;
fseek (file, 0, SEEK_END);
int size = ftell (file);
fseek (file, 0, SEEK_SET);
//rewind (file);
char *buffer = malloc (size);
fread (buffer, size, file);
fclose (file);
*/

int lecture_du_score (int quel_niveau);

void ecriture_du_score (int quel_niveau, int score);

char* nom_du_joueur (void);

#endif // SCORE_H_