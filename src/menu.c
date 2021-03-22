#include "main.h"

void afficher_menu(){
   printf("\n                                      ▄▄                           \n ▄█▀▀▀█▄█        ▀███                ▄██                           \n▄██    ▀█          ██                 ██                           \n▀███▄     ▄██▀██▄  ██  ▄██▀  ▄██▀██▄  ██▄████▄  ▄█▀██▄ ▀████████▄  \n  ▀█████▄██▀   ▀██ ██ ▄█    ██▀   ▀██ ██    ▀████   ██   ██    ██  \n▄     ▀████     ██ ██▄██    ██     ██ ██     ██ ▄█████   ██    ██  \n██     ████▄   ▄██ ██ ▀██▄  ██▄   ▄██ ██▄   ▄████   ██   ██    ██  \n█▀█████▀  ▀█████▀▄████▄ ██▄▄ ▀█████▀  █▀█████▀ ▀████▀██▄████  ████▄\n"); 
   sleep(2);
}

int choix_du_niveau(){
    int choix;
    printf("Choisis un niveau ! : ");
    scanf("%i",&choix);
    printf("\n%c\n", choix);

    return choix;
}

