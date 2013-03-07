/*
 * Here are all the functions related to game logic and structures.
 * For now it is standalone, but this should result in a library
 * for a dama game.
 */

#include "logic.h"

/*
 * This main will be ripped off in the future.
 */
int main()
{
	
	struct board b;
	
	printf("INFO: setting all initial board...");
	
	setAllBoardEmpty(&b);
	
	printf("done!\n");
	
	return 0;
}

/*
 * Print internal data board.
 */
void printBoard( struct board * b )
{
	// TODO: complete function that prints board
	// mainly for debug purposes
}

/*
 * Set all the data to empty data 'e' 
 */
void setAllBoardEmpty( struct board * b )
{	
	for (int i=0;i<8;i++){
		for (int j=0;j<8;j++){
			b->data[i][j] = 'e';
		}
	}
}
