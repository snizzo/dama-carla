/*
 * Here are all the functions related to game logic and structures.
 * For now it is standalone, but this should result in a library
 * for a dama game.
 */

#include "logic.h"


/*
 * This main will be ripped off in the future.
 */
 /*
int main()
{
	
	struct board b;
	
	printf("INFO: setting all initial board...");
	
	setAllBoardEmpty(&b);
	
	printf("done!\n");
	
	prepareBoard(&b);
	
	canMove( &b, 1);
	
	nextMove(&b, 3, 2, 1, 4, 1);

	printBoard(&b);
	
	mirrorBoard(&b);
	
	return 0;
}
*/
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
	int c = 0;													//orribile contatore che conta se c'è almeno una mossa che il
	if (m==1) {													//giocatore può fare
		c=0;
		for (int i=0;i<8;i++){
			for (int j=0;j<8;j++){
				if (b->data[i][j]==1) {
					if ((canWhiteMove(b, i, j)==1) || (canWhiteCapt(b, i, j)==1)) {
						c++;
					}
				} else if (b->data[i][j]==2) {
					if ((canWkingMove(b, i ,j)==1) || (canWkingCapt(b, i ,j)==1)) {
						c++;
					}
				}
			}
		}
	} else if (m==2) {
		c=0;
		for (int i=0;i<8;i++){
			for (int j=0;j<8;j++){
				if (b->data[i][j]==3) {
					if ((canBlackMove(b, i, j)==1) || (canBlackCapt(b, i, j)==1)) {
						c++;
					}
				} else if (b->data[i][j]==4) {
					if ((canBkingMove(b, i ,j)==1) || (canBkingCapt(b, i ,j)==1)) {
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

int canWhiteMove( struct board * b, int i, int j )				//può la pedina bianca muovere?
{
	if (j==0) {
		if (b->data[i-1][j+1]==0) {
			return 1;
		}
	} else if (j==7) {
		if (b->data[i-1][j-1]==0) {
			return 1;
		}
	} else {
		if (b->data[i-1][j-1]==0 || b->data[i-1][j+1]==0) {
			return 1;
		}
	}
	return -1;
}

int canWhiteCapt( struct board * b, int i, int j)						//può la pedina bianca mangiare?
{
	if (j==0) {
		if ((b->data[i-1][j+1]==3 || b->data[i-1][j+1]==4) && b->data[i-2][j+2]==0) {
			return 1;
		}
	} else if (j==7) {
		if ((b->data[i-1][j-1]==3 || b->data[i-1][j-1]==4) && b->data[i-2][j-2]==0) {
			return 1;
		}
	} else {
		if (((b->data[i-1][j+1]==3 || b->data[i-1][j+1]==4) && b->data[i-2][j+2]==0) || ((b->data[i-1][j-1]==3 || b->data[i-1][j-1]==4) && b->data[i-2][j-2]==0)) {
			return 1;
		}
	}
	return -1;
}

int canBlackMove( struct board * b, int i, int j )				//può la pedina nera muovere?
{
	if (j==0) {
		if (b->data[i+1][j+1]==0) {
			return 1;
		}
	} else if (j==7) {
		if (b->data[i+1][j-1]==0) {
			return 1;
		}
	} else {
		if (b->data[i+1][j-1]==0 || b->data[i+1][j+1]==0) {
			return 1;
		}
	}
	return -1;
}

int canBlackCapt( struct board * b, int i, int j)						//può la pedina nera mangiare?
{
	if (j==0) {
		if ((b->data[i+1][j+1]==1 || b->data[i+1][j+1]==2) && b->data[i+2][j+2]==0) {
			return 1;
		}
	} else if (j==7) {
		if ((b->data[i+1][j-1]==1 || b->data[i+1][j-1]==2) && b->data[i+2][j-2]==0) {
			return 1;
		}
	} else {
		if (((b->data[i+1][j+1]==1 || b->data[i+1][j+1]==2) && b->data[i+2][j+2]==0) || ((b->data[i+1][j-1]==1 || b->data[i+1][j-1]==2) && b->data[i+2][j-2]==0)) {
			return 1;
		}
	}
	return -1;
}

int canWkingMove( struct board * b, int i, int j )				//può la dama bianca muovere?
{
	if (i==0 && j==7) {
		if (b->data[i+1][j-1]==0) {
			return 1;
		}
	} else if (i==7 && j==0) {
		if (b->data[i-1][j+1]==0) {
			return 1;
		}
	} else if (i==0) {
		if (b->data[i+1][j+1]==0 || b->data[i+1][j-1]==0) {
				return 1;
		}
	} else if (i==7) {
		if (b->data[i-1][j+1]==0 || b->data[i-1][j-1]==0) {
				return 1;
		}
	} else if (j==0) {
		if (b->data[i+1][j+1]==0 || b->data[i-1][j+1]==0) {
				return 1;
		}
	} else if (j==7) {
		if (b->data[i+1][j-1]==0 || b->data[i-1][j-1]==0) {
				return 1;
		}
	} else {
		if (b->data[i+1][j+1]==0 || b->data[i+1][j-1]==0 || b->data[i-1][j+1]==0 || b->data[i-1][j-1]==0) {
				return 1;
		}
	}
	return -1;
}

int canWkingCapt( struct board * b, int i, int j )				//può la dama bianca mangiare?
{
	if (i==0 && j==7) {
		if ((b->data[i+1][j-1]==3 || b->data[i+1][j-1]==4) && b->data[i+2][j-2]==0) {
			return 1;
		}
	} else if (i==7 && j==0) {
		if ((b->data[i-1][j+1]==3 || b->data[i-1][j+1]==4) && b->data[i-2][j+2]==0) {
			return 1;
		}
	} else if (i==0) {
		if (((b->data[i+1][j+1]==3 || b->data[i+1][j+1]==4) && b->data[i+2][j+2]==0) ||
			((b->data[i+1][j-1]==3 || b->data[i+1][j-1]==4) && b->data[i+2][j-2]==0)) {
				return 1;
		}
	} else if (i==7) {
		if (((b->data[i-1][j+1]==3 || b->data[i-1][j+1]==4) && b->data[i-2][j+2]==0) ||
			((b->data[i-1][j-1]==3 || b->data[i-1][j-1]==4) && b->data[i-2][j-2]==0)) {
				return 1;
		}
	} else if (j==0) {
		if (((b->data[i+1][j+1]==3 || b->data[i+1][j+1]==4) && b->data[i+2][j+2]==0) ||
			((b->data[i-1][j+1]==3 || b->data[i-1][j+1]==4) && b->data[i-2][j+2]==0)) {
				return 1;
		}
	} else if (j==7) {
		if (((b->data[i+1][j-1]==3 || b->data[i+1][j-1]==4) && b->data[i+2][j-2]==0) ||
			((b->data[i-1][j-1]==3 || b->data[i-1][j-1]==4) && b->data[i-2][j-2]==0)) {
				return 1;
		}
	} else {
		if (((b->data[i+1][j+1]==3 || b->data[i+1][j+1]==4) && b->data[i+2][j+2]==0) ||
			((b->data[i+1][j-1]==3 || b->data[i+1][j-1]==4) && b->data[i+2][j-2]==0) ||
			((b->data[i-1][j+1]==3 || b->data[i-1][j+1]==4) && b->data[i-2][j+2]==0) ||
			((b->data[i-1][j-1]==3 || b->data[i-1][j-1]==4) && b->data[i-2][j-2]==0)) {
				return 1;
		}
	}
	return -1;
}

int canBkingMove( struct board * b, int i, int j )				//può la dama nera muovere?
{
	if (i==0 && j==7) {
		if (b->data[i+1][j-1]==0) {
			return 1;
		}
	} else if (i==7 && j==0) {
		if (b->data[i-1][j+1]==0) {
			return 1;
		}
	} else if (i==0) {
		if (b->data[i+1][j+1]==0 || b->data[i+1][j-1]==0) {
				return 1;
		}
	} else if (i==7) {
		if (b->data[i-1][j+1]==0 || b->data[i-1][j-1]==0) {
				return 1;
		}
	} else if (j==0) {
		if (b->data[i+1][j+1]==0 || b->data[i-1][j+1]==0) {
				return 1;
		}
	} else if (j==7) {
		if (b->data[i+1][j-1]==0 || b->data[i-1][j-1]==0) {
				return 1;
		}
	} else {
		if (b->data[i+1][j+1]==0 || b->data[i+1][j-1]==0 || b->data[i-1][j+1]==0 || b->data[i-1][j-1]==0) {
				return 1;
		}
	}
	return -1;
}

int canBkingCapt( struct board * b, int i, int j )				//può la dama nera mangiare?
{
	if (i==0 && j==7) {
		if ((b->data[i+1][j-1]==1 || b->data[i+1][j-1]==2) && b->data[i+2][j-2]==0) {
			return 1;
		}
	} else if (i==7 && j==0) {
		if ((b->data[i-1][j+1]==1 || b->data[i-1][j+1]==2) && b->data[i-2][j+2]==0) {
			return 1;
		}
	} else if (i==0) {
		if (((b->data[i+1][j+1]==1 || b->data[i+1][j+1]==2) && b->data[i+2][j+2]==0) ||
			((b->data[i+1][j-1]==1 || b->data[i+1][j-1]==2) && b->data[i+2][j-2]==0)) {
				return 1;
		}
	} else if (i==7) {
		if (((b->data[i-1][j+1]==1 || b->data[i-1][j+1]==2) && b->data[i-2][j+2]==0) ||
			((b->data[i-1][j-1]==1 || b->data[i-1][j-1]==2) && b->data[i-2][j-2]==0)) {
				return 1;
		}
	} else if (j==0) {
		if (((b->data[i+1][j+1]==1 || b->data[i+1][j+1]==2) && b->data[i+2][j+2]==0) ||
			((b->data[i-1][j+1]==1 || b->data[i-1][j+1]==2) && b->data[i-2][j+2]==0)) {
				return 1;
		}
	} else if (j==7) {
		if (((b->data[i+1][j-1]==1 || b->data[i+1][j-1]==2) && b->data[i+2][j-2]==0) ||
			((b->data[i-1][j-1]==1 || b->data[i-1][j-1]==2) && b->data[i-2][j-2]==0)) {
				return 1;
		}
	} else {
		if (((b->data[i+1][j+1]==1 || b->data[i+1][j+1]==2) && b->data[i+2][j+2]==0) ||
			((b->data[i+1][j-1]==1 || b->data[i+1][j-1]==2) && b->data[i+2][j-2]==0) ||
			((b->data[i-1][j+1]==1 || b->data[i-1][j+1]==2) && b->data[i-2][j+2]==0) ||
			((b->data[i-1][j-1]==1 || b->data[i-1][j-1]==2) && b->data[i-2][j-2]==0)) {
				return 1;
		}
	}
	return -1;
}


/*
 * i,j=coordinate pedina/dama da spostare; k,l=coordinate "arrivo"; m= 1 bianco 2 nero
 * prima di nextMove bisogna far chiamare al programma canMove, se canMove dà -1 la partita è finita e nextMove non parte
 * promemoria: capture controlla se una delle pedine che possono mangiare è quella selezionata dal giocatore. se lo è
 * e il giocatore ha selezionato la giusta casella per mangiare, modifica la board e il turno finisce, se una delle due
 * condizioni non è soddisfatta dice "devi mangiare per forza, rifai la mossa"; move funzionerà in modo simile
 * 
 * torna 1 se tutto bene,
 * torna -1 se tutto sbagliato
 * 
 */
int nextMove( struct board * b, struct moveinfo * move, int m )		//dà per scontato che la casella di partenza e quella di
{
	
	int i = 8 - atoi(move->daL);
	int j = 0;
	if (areEqual(move->daC, "a")) {
		j = 0;
	} else if (areEqual(move->daC, "b")) {
		j = 1;
	} else if (areEqual(move->daC, "c")) {
		j = 2;
	} else if (areEqual(move->daC, "d")) {
		j = 3;
	} else if (areEqual(move->daC, "e")) {
		j = 4;
	} else if (areEqual(move->daC, "f")) {
		j = 5;
	} else if (areEqual(move->daC, "g")) {
		j = 6;
	} else if (areEqual(move->daC, "h")) {
		j = 7;
	}
				
	int k = 8 - atoi(move->aL);
	int l = 0;
	if (areEqual(move->aC, "a")) {
		l = 0;
	} else if (areEqual(move->aC, "b")) {
		l = 1;
	} else if (areEqual(move->aC, "c")) {
		l = 2;
	} else if (areEqual(move->aC, "d")) {
		l = 3;
	} else if (areEqual(move->aC, "e")) {
		l = 4;
	} else if (areEqual(move->aC, "f")) {
		l = 5;
	} else if (areEqual(move->aC, "g")) {
		l = 6;
	} else if (areEqual(move->aC, "h")) {
		l = 7;
	}
																				//arrivo appartengano alla board
	if (m==1) {																//gioca il bianco
		if ((b->data[i][j]==1 || b->data[i][j]==2) && b->data[k][l]==0) {
			int c = 0;
			for (int d=0;d<8;d++){
				for (int e=0;e<8;e++){
					if (b->data[d][e]==1) {
						if (canWhiteCapt(b, d, e)==1) {
							c++;
						}
					} else if (b->data[d][e]==2) {
						if (canWkingCapt(b, d, e)==1) {
							c++;
						}
					}
				}
			}
			if (c>0) {
				capture(b, i, j, k, l);										//la riga successiva è la mangiata multipla
				return 1;
					//serve un nuovo input del giocatore che decide in che casella andare per mangiare,
					//a quel punto si richiama capture(b, k, l, (input del giocatore), (input del giocatore))
				
			} else {
				movement(b, i, j, k, l);
				return 1;
			}
		} else {
			printf ("quella non è una tua pedina/dama oppure la casella di destinazione non è libera\n");
			return -1;
		}
	} else {																//gioca il nero
		if ((b->data[i][j]==3 || b->data[i][j]==4) && b->data[k][l]==0) {
			int c = 0;
			for (int d=0;d<8;d++){
				for (int e=0;e<8;e++){
					if (b->data[d][e]==3) {
						if (canBlackCapt(b, d, e)==1) {
							c++;
						}
					} else if (b->data[d][e]==4){
						if(canBkingCapt(b, d, e)==1){
							c++;
						}
					}
				}
			}
			if (c>0) {
				capture(b, i, j, k, l);
				return 1;
			} else {
				movement(b, i, j, k, l);
				return 1;
			}
		} else {
			printf ("quella non è una tua pedina/dama oppure la casella di destinazione non è libera\n");
			return -1;
		}
	}
	
}

int movement( struct board * b, int i, int j, int k, int l)
{
	if (b->data[i][j]==1) {
		if (k==i-1 && (l==j+1 || l==j-1)) {
			changeBoard(b, i, j, 0);
			changeBoard(b, k, l, 1);
			return 1;
		} else {
			printf ("mossa non consentita\n");
			return -1;
		}
	} else if (b->data[i][j]==2) {
		if ((k==i+1 || k==i-1) && (l==j+1 || l==j-1)) {
			changeBoard(b, i, j, 0);
		    changeBoard(b, k, l, 2);
		    return 1;
		} else {
			printf ("mossa non consentita\n");
			return -1;
		}
	} else if (b->data[i][j]==3) {
		if (k==i+1 && (l==j+1 || l==j-1)) {
			changeBoard(b, i, j, 0);
			changeBoard(b, k, l, 3);
			return 1;
		} else {
			printf ("mossa non consentita\n");
			return -1;
		}
	} else if (b->data[i][j]==4) {
		if ((k==i+1 || k==i-1) && (l==j+1 || l==j-1)) {
			changeBoard(b, i, j, 0);
		    changeBoard(b, k, l, 4);
		    return 1;
		} else {
			printf ("mossa non consentita\n");
			return -1;
		}
	}
	return 1;
}

/*
 * se il capture va a buon fine, si dovrebbe verificare se la pedina che ha appena mangiato è ancora in grado di mangiare,
 * in quel caso bisogna farglielo fare però il giocatore dovrebbe decidere quale mangiare se può mangiarne più di una
 */
int capture( struct board *b, int i, int j, int k, int l)
{
	if (b->data[i][j]==1 && i==k+2 && (l==j-2 || l==j+2)) {
		if (b->data[(i+k)/2][(j+l)/2]==3 || b->data[(i+k)/2][(j+l)/2]==4) {
			changeBoard(b, i, j, 0);
			changeBoard(b, (i+k)/2, (j+l)/2, 0);
			changeBoard(b, k, l, 1);
			return 1;
		} else {
			printf ("mossa non consentita\n");
			return -1;
		}
	} else if (b->data[i][j]==2 && (i==k+2 || i==k-2) && (j==l-2 || j==l+2)) {
		if (b->data[(i+k)/2][(j+l)/2]==3 || b->data[(i+k)/2][(j+l)/2]==4) {
			changeBoard(b, i, j, 0);
			changeBoard(b, (i+k)/2, (j+l)/2, 0);
			changeBoard(b, k, l, 2);
			return 1;
		} else {
			printf ("mossa non consentita\n");
			return -1;
		}
	} else if (b->data[i][j]==3 && i==k-2 && (l==j-2 || l==j+2)) {
		if (b->data[(i+k)/2][(j+l)/2]==1 || b->data[(i+k)/2][(j+l)/2]==2) {
			changeBoard(b, i, j, 0);
			changeBoard(b, (i+k)/2, (j+l)/2, 0);
			changeBoard(b, k, l, 3);
			return 1;
		} else {
			printf ("mossa non consentita\n");
			return -1;
		}
	} else if (b->data[i][j]==4 && (i==k+2 || i==k-2) && (j==l-2 || j==l+2)) {
		if (b->data[(i+k)/2][(j+l)/2]==1 || b->data[(i+k)/2][(j+l)/2]==2) {
			changeBoard(b, i, j, 0);
			changeBoard(b, (i+k)/2, (j+l)/2, 0);
			changeBoard(b, k, l, 4);
			return 1;
		} else {
			printf ("mossa non consentita\n");
			return -1;
		}
	}
	return 1;
}
		


/*
 * i,j=coordinate da modificare. c=tipo di pedina
 */
void changeBoard( struct board * b, int i, int j,int c)
{
	if (i==0 && c==1) {
		b->data[i][j]=2;
	} else if (i==7 && c==3) {
		b->data[i][j]=4;
	} else {
		b->data[i][j]=c;
	}
}

void mirrorBoard( struct board * b)				//da modificare in base a come funzionerà il client
{
	int a[8][8];
	for (int i=0;i<8;i++){
		for (int j=0;j<8;j++){
			a[i][j]=b->data[7-i][7-j];
		}
	}
	printf ("\n\n");
	for (int i=0;i<8;i++){							//print per debug
		for (int j=0;j<8;j++){
			printf ("%i ", a[i][j]);
		}
		printf ("\n");
	}
}

/*
 * Print internal data board.
 */
void printBoard( struct board * b )
{	 
	for (int i=0;i<8;i++){
		for (int j=0;j<8;j++){
			printf ("%i ", b->data[i][j]);
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
