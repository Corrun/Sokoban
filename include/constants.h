#ifndef CONSTANTS_H_
#define CONSTANTS_H_

/*
— ’ ’ représente les cases vides
— ’#’ représente les murs (cases infranchissables)
— ’$’ représente une caisse que vous pouvez déplacer
— ’.’ représente une zone de rangement sur laquelle vous devez placer une caisse
— ’*’ représente une zone de rangement sur laquelle une caisse est actuellement placée
— ’@’ représente votre personnage
— ’+’ représente votre personnage lorsqu’il est sur une zone de rangement.
*/

#define TILE_EMPTY ' '
#define TILE_WALL '#'
#define TILE_CRATE '$'
#define TILE_TARGET '.'
#define TILE_CRATE_ON_TARGET '*'
#define TILE_PLAYER '@'
#define TILE_PLAYER_ON_TARGET '+'

#define DISPLAY_TILE_EMPTY ' '
#define DISPLAY_TILE_WALL '#'
#define DISPLAY_TILE_CRATE '$'
#define DISPLAY_TILE_TARGET '.'
#define DISPLAY_TILE_CRATE_ON_TARGET '*'
#define DISPLAY_TILE_PLAYER 'M'
#define DISPLAY_TILE_PLAYER_ON_TARGET '+'

#define DIR_UP 'z' // Touche permettant de se déplacer vers le haut
#define DIR_LEFT 'q' // Touche permettant de se déplacer vers la gauche
#define DIR_DOWN 's' // Touche permettant de se déplacer vers le bas
#define DIR_RIGHT 'd' // Touche permettant de se déplacer vers la droite
#define RESTART 'r' // Touche permettant de simuler la touche R, pendant un niveau, elle sert à recommencer le niveau
#define LEAVE 'l' // Touche permettant de simuler la touche L, pendant un niveau, elle sert à quitter le niveau
#define CANCEL 'a' // Touche permettant de simuler la touche A , pendant un niveau, elle sert à effectuer un retour arrière (annuler_deplacement)
#define HELP 'h' // Touche permettant de simuler la touche H, pendant un niveau, elle sert à afficher l'aide
 
#define KB_ENTER 10 // Touche permettant de simuler la touche entrée
#define KB_DOWN 258 // Touche permettant de se déplacer vers le bas
#define KB_UP 259 // Touche permettant de se déplacer vers le haut
#define KB_LEFT 260 // Touche permettant de se déplacer vers la gauche
#define KB_RIGHT 261 // Touche permettant de se déplacer vers la droite
#define KB_BACKSPACE 263 // Touche permettant de simuler la touche supprimer, pendant une demande de saisie, elle permet de supprimer du texte
#define KB_F1 265 // Touche permettant de simuler la touche fonction 1 (F1), pendant un niveau, elle sert à afficher l'aide

#define STATE_QUIT 0
#define STATE_MAINMENU 1

#define MAINMENU_PLAY 0
#define MAINMENU_RULES 1
#define MAINMENU_CONTROLS 2
#define MAINMENU_CREDITS 3
#define MAINMENU_SCOREBOARD 4
#define MAINMENU_QUIT 5

#define SCORE_BUFFER_SIZE 5

#endif // CONSTANTS_H_