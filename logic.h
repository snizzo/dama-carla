/*
 * In this file are container the game logic structure such as boards,
 * as well as function prototypes of "logic.c"
 */
#ifndef LOGIC_H
#define LOGIC_H

#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "network.h"

//data board values:
//	0	: empty
//	1   : white checker (pedina)
//	3   : black checker (pedina)
//	2   : white king
//	4   : black king

void prepareBoard( struct board * b );
void printBoard( struct board * b );
void setAllBoardEmpty( struct board * b );
int canMove ( struct board * b, int m);
int canWhiteMove( struct board * b, int i, int j );
int canWhiteCapt( struct board * b, int i, int j );
int canBlackMove( struct board * b, int i, int j );
int canBlackCapt( struct board * b, int i, int j );
int canWkingMove( struct board * b, int i, int j );
int canWkingCapt( struct board * b, int i, int j );
int canBkingMove( struct board * b, int i, int j );
int canBkingCapt( struct board * b, int i, int j );
int movement( struct board * b, int i, int j, int k, int l);
int capture( struct board *b, int i, int j, int k, int l);
void changeBoard( struct board * b, int i, int j,int c);
void mirrorBoard( struct board * b);
void printAfterMove(struct board * b);
int nextMove( struct board * b, struct moveinfo * d, int m );


#endif
