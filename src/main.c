#include "main.h"

int main(void) {
  initialiser_ncurses();
  
  /*niveau_t* niveau = lecture_du_niveau(0);
  deplacement(niveau, DIR_LEFT);
  annuler_deplacement(niveau);
  affichage_niveau_ncurses(niveau);*/

  int state = STATE_MAINMENU;

  while (state != STATE_QUIT) {
    switch(state) {
      case STATE_MAINMENU:
        switch (afficher_menu_principal()) {
          case MAINMENU_PLAY:;
            int numero_niveau = choix_du_niveau();
            jouer(numero_niveau);
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

  fermer_ncurses();
  return 0;
}
