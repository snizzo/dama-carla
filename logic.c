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
	
	canMove( &b, 1);
	
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

/*
 * se un giocatore al suo turno non può muovere niente, perde: se c>0 può muovere, se c=0 partita persa per il giocatore di turno
 */
int canMove ( struct board * b, int m)
{
	int c;													//orribile contatore che conta se c'è almeno una mossa che il
	if (m==1) {												//giocatore può fare
		c=0;	
		for (int i=0;i<8;i++){
			for (int j=0;j<8;j++){
				if (b->data[i][j]==1) {
					if (canMoveWhite(&b, i, j)==1) {
						c++;
					}
				} else if (b->data[i][j]==2) {
					if (canMoveWhite(&b, i ,j)==1) {
						c++;
					}
				}
			}
		}
	} else if (m==2) {
		int c;
		c=0;
		for (int i=0;i<8;i++){
			for (int j=0;j<8;j++){
				if (b->data[i][j]==3) {
					if (canMoveBlack(&b, i, j)==1) {
						c++;
					}
				} else if (b->data[i][j]==4) {
					if (canMoveBlack(&b, i ,j)==1) {
						c++;
					}
				}
			}
		}
	}
	if (c==0) {
		printf ("perso\n");
		return -1;
		} else {
			printf ("ci sono mosse\n");
			return 1;
			}
}

int canMoveWhite( struct board * b, int i, int j )			//può la pedina bianca muovere?
{
	if (j==0) {
		if (b->data[i-1][j+1]==0 || ((b->data[i-1][j+1]==3 || b->data[i-1][j+1]==4) && b->data[i-2][j+2]==0)) {
			return 1;
		}
	} else if (j==7) {
		if (b->data[i-1][j-1]==0 || ((b->data[i-1][j-1]==3 || b->data[i-1][j-1]==4) && b->data[i-2][j-2]==0)) {
			return 1;
		}
	} else {
		if (b->data[i-1][j-1]==0 || b->data[i-1][j+1]==0 || ((b->data[i-1][j+1]==3 || b->data[i-1][j+1]==4) && b->data[i-2][j+2]==0) || ((b->data[i-1][j-1]==3 || b->data[i-1][j-1]==4) && b->data[i-2][j-2]==0)) {
			return 1;
		}
	}
}

int canMoveBlack( struct board * b, int i, int j )			//può la pedina nera muovere?
{
	if (j==0) {
		if (b->data[i+1][j+1]==0 || ((b->data[i+1][j+1]==3 || b->data[i+1][j+1]==4) && b->data[i+2][j+2]==0)) {
			return 1;
		}
	} else if (j==7) {
		if (b->data[i+1][j-1]==0 || ((b->data[i+1][j-1]==3 || b->data[i+1][j-1]==4) && b->data[i+2][j-2]==0)) {
			return 1;
		}
	} else {
		if (b->data[i+1][j-1]==0 || b->data[i+1][j+1]==0 || ((b->data[i+1][j+1]==3 || b->data[i+1][j+1]==4) && b->data[i+2][j+2]==0) || ((b->data[i+1][j-1]==3 || b->data[i+1][j-1]==4) && b->data[i+2][j-2]==0)) {
			return 1;
		}
	}
}

//int canMove2( struct board * b, int i, int j )			//può la dama bianca muovere?
//{
//	if (i==0 && j==0) {
//		if (b->data[i+1][j+1]==0 || ((b->data[i+1][j+1]==3 || b->data[i+1][j+1]==4) && b->data[i+2][j+2]==0)) {
//			return 1;
//		}
//	} else if (i==0 && j==7) {
//		if (b->data[i+1][j-1]==0 || ((b->data[i+1][j-1]==3 || b->data[i+1][j-1]==4) && b->data[i+2][j-2]==0)) {
//			return 1;
//		}
//	} else if (i==7 && j==0) {
//		if (b->data[i-1][j+1]==0 || ((b->data[i-1][j+1]==3 || b->data[i-1][j+1]==4) && b->data[i-2][j+2]==0)) {
//			return 1;
//		}
//	} else if (i==7 && j==7) {
//		if (b->data[i-1][j-1]==0 || ((b->data[i-1][j-1]==3 || b->data[i-1][j-1]==4) && b->data[i-2][j-2]==0)) {
//			return 1;
//		}
//	} else if 





/*
 * i,j=coordinate pedina/dama da spostare; k,l=coordinate "arrivo"; m= 1 bianco 2 nero
 */
int nextMove( struct board * b, int i, int j, int k, int l, int m )		//dà per scontato che la casella di partenza e quella di
{																			//arrivo appartengano alla board
	
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
