#include "main.h"

int main(void){
  /*niveau_t* niv1 = nouveau_niveau(10,10);
  initialise_terrain(niv1);
  printf("1\n");
  place_sur_terrain(niv1,4,2,TILE_EMPTY);
  place_sur_terrain(niv1,6,5,TILE_EMPTY);
  printf("1\n");
  affichage_niveau(niv1);*/
  
  //niveau_t* niveau = lecture_du_niveau(2);
  //affichage_niveau(niveau);

  niveau_t* niveau = lecture_du_niveau(0);
  affichage_niveau(niveau);

  //entree_du_joueur();
  return 0;
}
