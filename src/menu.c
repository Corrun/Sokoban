#include "main.h"

// Affiche le niveau de manière (très) brut.
void afficher_menu(){
   printf("\n                                      ▄▄                           \n ▄█▀▀▀█▄█        ▀███                ▄██                           \n▄██    ▀█          ██                 ██                           \n▀███▄     ▄██▀██▄  ██  ▄██▀  ▄██▀██▄  ██▄████▄  ▄█▀██▄ ▀████████▄  \n  ▀█████▄██▀   ▀██ ██ ▄█    ██▀   ▀██ ██    ▀████   ██   ██    ██  \n▄     ▀████     ██ ██▄██    ██     ██ ██     ██ ▄█████   ██    ██  \n██     ████▄   ▄██ ██ ▀██▄  ██▄   ▄██ ██▄   ▄████   ██   ██    ██  \n█▀█████▀  ▀█████▀▄████▄ ██▄▄ ▀█████▀  █▀█████▀ ▀████▀██▄████  ████▄\n"); 
   sleep(2);
}

// Permet de demander à l'utilisateur un int, pour ensuite choisir le niveau
int choix_du_niveau(){
    int choix;
    printf("Choisis un niveau ! : ");
    scanf("%i",&choix);
    printf("\n%c\n", choix);

    return choix;
}

