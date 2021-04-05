#include "main.h"

int main(void){
  int instruction;
  system("clear");
  // FIX Mettre dans une fonction alternative, pour externaliser le jeu et pouvoir relancer un niveau sans soucis (par exemple)
  afficher_menu();

  instruction = scanf("%d",&instruction);

  instruction_menu(instruction);
 

  affichage_niveau(niveau);
  do{
    system("clear");
    printf("Nombre de coups: %d\n", niveau->nb_de_pas);
    affichage_niveau(niveau);
    char direction = entree_du_joueur();
    if(direction == LEAVE){
      break;
    }
    deplacement(niveau, direction);
  }while(nombre_de_caisse_restante_sur_terrain(niveau) != 0);

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

  liberation_du_niveau(niveau);

  return 0;
}
