#include "../include/main.h"



char entree_du_joueur(void){
  
  int var;
  do
  {
    var = getchar();
  } while (var != 'z');
  printf("%c\n",var);
  return var;
}

