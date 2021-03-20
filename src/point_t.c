#include "../include/main.h"



char entree_du_joueur(void){
  initscr();
  int var;
  var = getchar();
  
  printf("%c\n",var);
  return var;
}

