#include "../include/main.h"



char entree_du_joueur(void){
  
  int var;
  do
  {
    var = getchar();
  } while (var != 'z' && var != 'q' && var != 's' && var != 'd');
  printf("%c\n",var);
  return var;
}

