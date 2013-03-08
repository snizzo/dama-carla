/*
 * In this file are container the game logic structure such as boards,
 * as well as function prototypes of "logic.c"
 */
#ifndef LOGIC_H
#define LOGIC_H

#include <stdio.h>


//data board values:
//	e	: empty
//	w   : white checker (pedina)
//	b   : black checker (pedina)
//	W   : white dama
//	B   : black dama
struct board{
	int data[8][8];
};

void printBoard( struct board * b );
void setAllBoardEmpty(struct board * b);

#endif
