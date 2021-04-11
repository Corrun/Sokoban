#include "main.h"

// D'où s'exécute tout le jeu
// L'origine de tout
int main(void) {
  afficher_logo(); // On affiche le (magnifique) logo
  sleep(3); // On met en pose le programme 3 secondes

  // Initialisation de l'interface graphique (mode texte avancé NCurses)
  initialiser_ncurses();
  
  int numero_niveau; // On déclare la variable ici au lieu de la placer dans un case du switch pour éviter les erreurs

  int state = STATE_MAINMENU; // Contient l'état actuel de la navigation

  while (state != STATE_QUIT) { // tant que l'état n'est pas "quitter"
    switch(state) {
      case STATE_MAINMENU:
        switch (afficher_menu_principal()) {
          case MAINMENU_PLAY:; // Si l'option choisie est "Jouer"
            numero_niveau = choix_du_niveau(); // On demande le niveau que le joueur souhaite jouer
            jouer_niveau(numero_niveau); // On met le niveau en route correspondant à "numero_niveau"
            break;
          case MAINMENU_RULES:; // Si l'option choisie est "Règles"
            afficher_regles(); // On affiche les règles
            break;
          case MAINMENU_CONTROLS:; // Si l'option choisie est "Controles"
            afficher_controles(); // On affche les controles
            break;
          case MAINMENU_CREDITS:; // Si l'option choisie est "Credits"
            afficher_credits(); // On affiche les credits
            break;
          case MAINMENU_SCOREBOARD:; // Si l'option choisie est "Leaderboards"
            numero_niveau = choix_du_niveau(); // On demande le niveau dont le joueur souhaite voir les scores
            afficher_liste_niveau_scoreboard(numero_niveau); // On affiche un tableau de score du niveau correspondant à "numero_niveau"
            break;
          case MAINMENU_QUIT:; // Si l'option choisie est "Quitter"
            if (afficher_menu_quitter() == 1) { // Si l'utilisateur sélectionne "Oui"
              // On met l'état sur "quitter"
              // Ce qui fait sortir de la boucle principale et quitte le programme
              state = STATE_QUIT; 
            }
            break;
        }
        break;
    }
  }

  fermer_ncurses(); // Fermer toutes les fenêtres NCurses et revenir au mode texte simple
  system("clear"); // Permet d'enlever le logo, sans ça, il reste et c'est moche ¯\_(ツ)_/¯.
  return 0; 
}
