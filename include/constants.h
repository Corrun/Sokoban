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

#define DIR_UP 'z'
#define DIR_LEFT 'q'
#define DIR_DOWN 's'
#define DIR_RIGHT 'd'
#define RESTART 'r'
#define LEAVE 'l'
#define CANCEL 'a'
#define HELP 'h'

#define KB_ENTER 10
#define KB_DOWN 258
#define KB_UP 259
#define KB_LEFT 260
#define KB_RIGHT 261
#define KB_BACKSPACE 263
#define KB_F1 265

#define STATE_QUIT 0
#define STATE_MAINMENU 1

#define MAINMENU_PLAY 0
#define MAINMENU_RULES 1
#define MAINMENU_CREDITS 2
#define MAINMENU_SCOREBOARD 3
#define MAINMENU_QUIT 4

#define SCORE_BUFFER_SIZE 5

#endif // CONSTANTS_H_