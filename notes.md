Lire le score

On sélectionne le niveau N
On ouvre niveau_n
On ouvre score_n

Si le fichier score n'existe pas, retourner valeur d'erreur (-1 ?)

Sinon, parcourir ligne par ligne et conserver valeur max à chaque fois...

Retourner valeur en fin de parcours

Liste fonctions ? :
point.h > char entree_du_joueur (void)
niveau.h > liberation_de_la_liste_niveaux(liste_niveaux_t* liste)
niveau.h > affichage_niveau()
menu.h > afficher_logo()
    On ne s'en sert pas mais, peut être utile
menu.c > afficher_liste_niveau_scoreboard
    Fonction non fini
menu.h > instruction_menu()
    Fonction déplacée dans main ?
menu.h > menu_saisie_texte()
    Cassée ?????




struct score
    int points
    char* username



file format:
```
3
17 bertrand



```








score_multi_n

3
47 foo
54 bar
67 hello_sailor




Faire menu message qui lit depuis un fichier
Faire menu scoreboard