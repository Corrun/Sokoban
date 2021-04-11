#include "main.h"

int main(void) {
  /*liste_score_t* scores = lire_liste_scores(0);
  
  return 0;*/
  //afficher_logo();
  //sleep(5);

  initialiser_ncurses();
  
  int numero_niveau;

  int state = STATE_MAINMENU;
  while (state != STATE_QUIT) {
    switch(state) {
      case STATE_MAINMENU:
        switch (afficher_menu_principal()) {
          case MAINMENU_PLAY:;
            numero_niveau = choix_du_niveau();
            jouer_niveau(numero_niveau);
            break;
          case MAINMENU_RULES:;
            afficher_regles();
            break;
          case MAINMENU_CREDITS:;
            afficher_credits();
            break;
          case MAINMENU_SCOREBOARD:;
            numero_niveau = choix_du_niveau();
            afficher_liste_niveau_scoreboard(numero_niveau); // Cette fonction permetterai de lister les fichiers niveau/niveau_%d (menu deroulant si possible)
            break;
          case MAINMENU_QUIT:;
            if (afficher_menu_quitter() == 1) {
              state = STATE_QUIT;
            }
            break;
        }

        break;
    }
  }

  fermer_ncurses();
  return 0;
}
