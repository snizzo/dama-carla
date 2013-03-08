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
	
	prepareBoard(&b);
	
	nextMove(&b, 5, 2, 4, 3, 1);

	printBoard(&b);
	
	return 0;
}

void prepareBoard( struct board * b )
{
	b->data[0][7] = 3;
	b->data[0][5] = 3;
	b->data[0][3] = 3;
	b->data[0][1] = 3;
	
	b->data[1][6] = 3;
	b->data[1][4] = 3;
	b->data[1][2] = 3;
	b->data[1][0] = 3;
	
	b->data[2][7] = 3;
	b->data[2][5] = 3;
	b->data[2][3] = 3;
	b->data[2][1] = 3;
	
	b->data[7][6] = 1;
	b->data[7][4] = 1;
	b->data[7][2] = 1;
	b->data[7][0] = 1;
	
	b->data[5][6] = 1;
	b->data[5][4] = 1;
	b->data[5][2] = 1;
	b->data[5][0] = 1;
	
	b->data[6][7] = 1;
	b->data[6][5] = 1;
	b->data[6][3] = 1;
	b->data[6][1] = 1;

}

int nextMove( struct board * b, int i, int j, int k, int l, int m ) //i,j: coordinate pedina da muovere. k,l: coord. "destinazione". m:1 bianco 2: nero
{
	if (b->data[i][j]==0 || i>7 || j>7 || k>7 || l>7) {				//il genio tenta di muovere una pedina che non esiste
		printf ("nonnònnò\n");
	} else {
		if (m==1) {													//giocatore bianco muove
			if (b->data[i-1][j-1]==0 && (k==i+1 || l==j-1)) {		//bianco muove a sinistra
				b->data[i][j] = 0;
				b->data[i-1][j-1] = 1;
			} else if (b->data[i-1][j+1]==0 && (k==i+1 || l==j+1)) {		//bianco muove a destra
				b->data[i][j] = 0;
				b->data[i-1][j+1] = 1;
			}
		}
	}
}

/*
 * Print internal data board.
 */
void printBoard( struct board * b )
{	
	for (int i=0;i<8;i++){
		for (int j=0;j<8;j++){
			printf ("%i", b->data[i][j]);
		}
		printf ("\n");
	}
	
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
			b->data[i][j] = 0;
		}
	}
}
