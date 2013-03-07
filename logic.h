/*
 * In this file are container the game logic structure such as boards,
 * as well as function prototypes of "logic.c"
 */
#ifndef LOGIC_H
#define LOGIC_H

#include <stdio.h>


//data board values:
//	'e'	: empty
//	'wc': white checker (pedina)
//	'bc': black checker (pedina)
//	'wd': white dama
//	'bd': black dama
struct board{
	char data[8][8];
};

void printBoard( struct board * b );
void setAllBoardEmpty(struct board * b);

#endif
