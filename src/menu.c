#include "main.h"

// Affiche le niveau de manière (très) brut.
void afficher_logo(){
   printf("\n                                      ▄▄                           \n ▄█▀▀▀█▄█        ▀███                ▄██                           \n▄██    ▀█          ██                 ██                           \n▀███▄     ▄██▀██▄  ██  ▄██▀  ▄██▀██▄  ██▄████▄  ▄█▀██▄ ▀████████▄  \n  ▀█████▄██▀   ▀██ ██ ▄█    ██▀   ▀██ ██    ▀████   ██   ██    ██  \n▄     ▀████     ██ ██▄██    ██     ██ ██     ██ ▄█████   ██    ██  \n██     ████▄   ▄██ ██ ▀██▄  ██▄   ▄██ ██▄   ▄████   ██   ██    ██  \n█▀█████▀  ▀█████▀▄████▄ ██▄▄ ▀█████▀  █▀█████▀ ▀████▀██▄████  ████▄\n"); 
}

// Permet de demander à l'utilisateur un int, pour ensuite choisir le niveau
int choix_du_niveau(){
    int choix;
    printf("Choisis un niveau ! : ");
    scanf("%i",&choix);
    printf("\n%c\n", choix);

    return choix;
}

void afficher_regles(){
    printf("voir github\nPress Q to leave");
}

void afficher_credits(){
    printf("amaury néo et hugo\nPress Q to leave");
}

void instruction_menu(int instruction){
    int leave;
    switch (instruction){
    case 1: //Jouer
        int niveau_actuel = choix_du_niveau();
        niveau_t* niveau = lecture_du_niveau(niveau_actuel);
        int high_score = lecture_du_score(niveau_actuel);
        break;
    case 2: //Règles
        do{
            system("clear");
            afficher_regles();
            leave = scanf("%d",&leave);
        }while(leave == 'q' && leave == 'Q');
        break;        

     case 3: //Crédits
        do{
            system("clear");
            afficher_credits();
            leave = scanf("%d",&leave);
        }while(leave == 'q' && leave == 'Q');
        break;
    
     case 4: //Quitter
        printf("todo");
        break;

    default:
        return;
    }
}

