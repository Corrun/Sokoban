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

#define DIR_UP 'z'
#define DIR_LEFT 'q'
#define DIR_DOWN 's'
#define DIR_RIGHT 'd'
#define RESTART 'r'

#endif // CONSTANTS_H_