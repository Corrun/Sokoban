#include <stdio.h>
#include <stdlib.h>
#include "struct/niveau_t.h"
#include "constants.h"

int main(void){
  /*  niveau_t* niv1 = nouveau_niveau(10,10);
  initialise_terrain(niv1);
  printf("1\n");
  place_sur_terrain(niv1,4,2,TILE_EMPTY);
  printf("1\n");
  affichage_niveau(niv1);*/
  niveau_t* niv0 = lecture_du_niveau(0);
  affichage_niveau(niv0);
  return 0;
}
