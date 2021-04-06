#include "main.h"

int main(void){
  initialiser_ncurses();
  
  int state = STATE_MAINMENU;

  while (state != STATE_QUIT) {
    switch(state) {
      case STATE_MAINMENU:
        switch (afficher_menu_principal()) {
          case MAINMENU_PLAY:;
            int numero_niveau = choix_du_niveau();
            niveau_t* niveau = lecture_du_niveau(numero_niveau);
            affichage_niveau_ncurses(niveau);
            break;
          case MAINMENU_RULES:;

            break;
          case MAINMENU_CREDITS:;

            break;
          case MAINMENU_QUIT:
            state = STATE_QUIT;
            break;
        }

        break;
    }
  }

  //afficher_menu_principal();
  
  fermer_ncurses();
  
  /*int instruction;
  system("clear");
  // FIX Mettre dans une fonction alternative, pour externaliser le jeu et pouvoir relancer un niveau sans soucis (par exemple)
  afficher_logo();

  instruction = scanf("%d",&instruction);

  int niveau_actuel = choix_du_niveau();
  niveau_t* niveau = lecture_du_niveau(niveau_actuel);
  int high_score = lecture_du_score(niveau_actuel);

  instruction_menu(instruction);
 
  affichage_niveau(niveau);
  do{
    system("clear");
    printf("Nombre de coups: %d\n", niveau->nb_de_pas);
    affichage_niveau(niveau);
    char direction = entree_du_joueur();
    if(direction == LEAVE) {
      break;
    }
    deplacement(niveau, direction);
  } while(nombre_de_caisse_restante_sur_terrain(niveau) != 0);

  system("clear");
  affichage_niveau(niveau);

  if(nombre_de_caisse_restante_sur_terrain(niveau)==0){

    printf("Bravo, tu as terminé le niveau %d en %d coups", niveau_actuel, niveau->nb_de_pas);
    if (high_score == -1 ||  niveau->nb_de_pas < high_score){
      // Nouveau high score
      ecriture_du_score(niveau_actuel, niveau->nb_de_pas);
      printf(" (nouveau high score)");
    }
    printf("\n");
    //printf("GG T'AS FINI LE JEU EN %d COUPS !!!!!!!!!!!\n", niveau->nb_de_pas);
    
    nom_du_joueur();

    // FIX > Add la fonction pour ajouter le meilleur score //// On garde quoi ? Les 3 meilleurs ???
  }else{
    printf("Quel ragequit de la part du joueur français!\n");
  }

  liberation_du_niveau(niveau);*/

  return 0;
}
