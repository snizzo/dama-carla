/*
 * Here are all the functions related to game logic and structures.
 * For now it is standalone, but this should result in a library
 * for a dama game.
 */

#include "logic.h"

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
 * canMove: -1=game lost
 */
int canMove ( struct board * b, int m )
{
	int c = 0;
	if (m==1) {
		c=0;
		for (int d=0;d<8;d++){
			for (int e=0;e<8;e++){
				if (b->data[d][e]==1) {
					if ((canWhiteMove(b, d, e)==1) || ((canWhiteCapt(b, e, d-1, e-1)==1) || (canWhiteCapt(b, e, d-1, e+1)==1))) {
						c++;
					}
				} else if (b->data[d][e]==2) {
					if ((canWkingMove(b, d, e)==1) || ((canWkingCapt(b, d, e, d-1, e-1)==1) || (canWkingCapt(b, d, e, d-1, e+1)==1) ||
													   (canWkingCapt(b, d, e, d+1, e-1)==1) || (canWkingCapt(b, d, e, d+1, e+1)==1))) {
						c++;
					}
				}
			}
		}
	} else if (m==2) {
		c=0;
		for (int d=0;d<8;d++){
			for (int e=0;e<8;e++){
				if (b->data[d][e]==3) {
					if ((canBlackMove(b, d, e)==1) || ((canBlackCapt(b, e, d+1, e-1)==1) || (canBlackCapt(b, e, d+1, e+1)==1))) {
						c++;
					}
				} else if (b->data[d][e]==4) {
					if ((canBkingMove(b, d ,e)==1) || ((canBkingCapt(b, d, e, d+1, e-1)==1) || (canBkingCapt(b, d, e, d+1, e+1)==1) ||
													   (canBkingCapt(b, d, e, d-1, e-1)==1) || (canBkingCapt(b, d, e, d-1, e+1)==1))) {
						c++;
					}
				}
			}
		}
	}
	if (c==0) {
		return -1;
		} else {
			return 1;
			}
}

int canWhiteMove( struct board * b, int i, int j )							//can white checker move?
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

int canWhiteCapt( struct board * b, int j, int k, int l)						//can white checker capture?
{
	if (notCapturable(k, l)==1) {
		return -1;
	} else if (j==0) {
		if ((b->data[k][l]==3 || b->data[k][l]==4) && b->data[k-1][l+1]==0) {
			return 1;
		}
	} else if (j==7) {
		if ((b->data[k][l]==3 || b->data[k][l]==4) && b->data[k-1][l-1]==0) {
			return 1;
		}
	} else {
		if ((b->data[k][l]==3 || b->data[k][l]==4) && b->data[k-1][l+(l-j)]==0) {
			return 1;
		}
	}
	return -1;
}

int canBlackMove( struct board * b, int i, int j )							//can black checker move?
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

int canBlackCapt( struct board * b, int j, int k, int l)						//can black checker capture?
{
	if (notCapturable(k, l)==1) {
		return -1;
	} else if (j==0) {
		if ((b->data[k][l]==1 || b->data[k][l]==2) && b->data[k+1][l+1]==0) {
			return 1;
		}
	} else if (j==7) {
		if ((b->data[k][l]==1 || b->data[k][l]==2) && b->data[k+1][l-1]==0) {
			return 1;
		}
	} else {
		if ((b->data[k][l]==1 || b->data[k][l]==2) && b->data[k+1][l+(l-j)]==0) {
			return 1;
		}
	}
	return -1;
}

int canWkingMove( struct board * b, int i, int j )							//can white king move?
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

int canWkingCapt( struct board * b, int i, int j, int k, int l)				//can white king capture?
{
	if (notCapturable(k, l)==1) {
		return -1;
	} else if (i==0 && j==7) {
		if ((b->data[k][l]==3 || b->data[k][l]==4) && b->data[k+1][l-1]==0) {
			return 1;
		}
	} else if (i==7 && j==0) {
		if ((b->data[k][l]==3 || b->data[k][l]==4) && b->data[k-1][l+1]==0) {
			return 1;
		}
	} else if (i==0) {
		if ((b->data[k][l]==3 || b->data[k][l]==4) && b->data[k+1][l+(l-j)]==0) {
				return 1;
		}
	} else if (i==7) {
		if ((b->data[k][l]==3 || b->data[k][l]==4) && b->data[k-1][l+(l-j)]==0) {
				return 1;
		}
	} else if (j==0) {
		if ((b->data[k][l]==3 || b->data[k][l]==4) && b->data[k+(k-i)][l+1]==0) {
				return 1;
		}
	} else if (j==7) {
		if ((b->data[k][l]==3 || b->data[k][l]==4) && b->data[k+(k-i)][l-1]==0) {
				return 1;
		}
	} else {
		if ((b->data[k][l]==3 || b->data[k][l]==4) && b->data[k+(k-i)][l+(l-j)]==0) {
				return 1;
		}
	}
	return -1;
}

int canBkingMove( struct board * b, int i, int j )							//can black king move?
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

int canBkingCapt( struct board * b, int i, int j, int k, int l)				//can black king capture?
{
	if (notCapturable(k, l)==1) {
		return -1;
	} else if (i==0 && j==7) {
		if ((b->data[k][l]==1 || b->data[k][l]==2) && b->data[k+1][l-1]==0) {
			return 1;
		}
	} else if (i==7 && j==0) {
		if ((b->data[k][l]==1 || b->data[k][l]==2) && b->data[k-1][l+1]==0) {
			return 1;
		}
	} else if (i==0) {
		if ((b->data[k][l]==1 || b->data[k][l]==2) && b->data[k+1][l+(l-j)]==0) {
				return 1;
		}
	} else if (i==7) {
		if ((b->data[k][l]==1 || b->data[k][l]==2) && b->data[k-1][l+(l-j)]==0) {
				return 1;
		}
	} else if (j==0) {
		if ((b->data[k][l]==1 || b->data[k][l]==2) && b->data[k+(k-i)][l+1]==0) {
				return 1;
		}
	} else if (j==7) {
		if ((b->data[k][l]==1 || b->data[k][l]==2) && b->data[k+(k-i)][l-1]==0) {
				return 1;
		}
	} else {
		if ((b->data[k][l]==1 || b->data[k][l]==2) && b->data[k+(k-i)][l+(l-j)]==0) {
				return 1;
		}
	}
	return -1;
}


/*
 * nextMove:	1=move done		-1=move not done
 */
int nextMove( struct board * b, struct moveinfo * move, int m )
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

	if (m==1) {																	//white player plays
		if ((b->data[i][j]==1 || b->data[i][j]==2) && b->data[k][l]==0) {
			int c = 0;
			for (int d=0;d<8;d++){
				for (int e=0;e<8;e++){
					if (b->data[d][e]==1) {
						if ((canWhiteCapt(b, e, d-1, e-1)==1) || (canWhiteCapt(b, e, d-1, e+1)==1)) {
							c++;
						}
					} else if (b->data[d][e]==2) {
						if ((canWkingCapt(b, d, e, d-1, e-1)==1) || (canWkingCapt(b, d, e, d-1, e+1)==1) ||
							(canWkingCapt(b, d, e, d+1, e-1)==1) || (canWkingCapt(b, d, e, d+1, e+1)==1)) {
							c++;
						}
					}
				}
			}
			if (c>0) {
				if (capture(b, i, j, k, l)==1) {
					return 1;
				} else {
					return -1;
				}
			} else {
				if (movement(b, i, j, k, l)==1) {
					return 1;
				} else {
					return -1;
				}
			}
		} else {
			return -1;
		}
	} else {																	//black player plays
		if ((b->data[i][j]==3 || b->data[i][j]==4) && b->data[k][l]==0) {
			int c = 0;
			for (int d=0;d<8;d++){
				for (int e=0;e<8;e++){
					if (b->data[d][e]==3) {
						if ((canBlackCapt(b, e, d+1, e-1)==1) || (canBlackCapt(b, e, d+1, e+1)==1)) {
							c++;
						}
					} else if (b->data[d][e]==4){
						if ((canBkingCapt(b, d, e, d+1, e-1)==1) || (canBkingCapt(b, d, e, d+1, e+1)==1) ||
							(canBkingCapt(b, d, e, d-1, e-1)==1) || (canBkingCapt(b, d, e, d-1, e+1)==1)) {
							c++;
						}
					}
				}
			}
			if (c>0) {
				if (capture(b, i, j, k, l)==1) {
					return 1;
				} else {
					return -1;
				}
			} else {
				if (movement(b, i, j, k, l)==1) {
					return 1;
				} else {
					return -1;
				}
			}
		} else {
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
			return -1;
		}
	} else if (b->data[i][j]==2) {
		if ((k==i+1 || k==i-1) && (l==j+1 || l==j-1)) {
			changeBoard(b, i, j, 0);
		    changeBoard(b, k, l, 2);
		    return 1;
		} else {
			return -1;
		}
	} else if (b->data[i][j]==3) {
		if (k==i+1 && (l==j+1 || l==j-1)) {
			changeBoard(b, i, j, 0);
			changeBoard(b, k, l, 3);
			return 1;
		} else {
			return -1;
		}
	} else if (b->data[i][j]==4) {
		if ((k==i+1 || k==i-1) && (l==j+1 || l==j-1)) {
			changeBoard(b, i, j, 0);
		    changeBoard(b, k, l, 4);
		    return 1;
		} else {
			return -1;
		}
	}
	return -1;
}

int capture( struct board *b, int i, int j, int k, int l)
{
	if (b->data[i][j]==1 && i==k+2 && (l==j-2 || l==j+2)) {
		if (b->data[(i+k)/2][(j+l)/2]==3 || b->data[(i+k)/2][(j+l)/2]==4) {
			changeBoard(b, i, j, 0);
			changeBoard(b, (i+k)/2, (j+l)/2, 0);
			changeBoard(b, k, l, 1);
			return 1;
		} else {
			return -1;
		}
	} else if (b->data[i][j]==2 && (i==k+2 || i==k-2) && (j==l-2 || j==l+2)) {
		if (b->data[(i+k)/2][(j+l)/2]==3 || b->data[(i+k)/2][(j+l)/2]==4) {
			changeBoard(b, i, j, 0);
			changeBoard(b, (i+k)/2, (j+l)/2, 0);
			changeBoard(b, k, l, 2);
			return 1;
		} else {
			return -1;
		}
	} else if (b->data[i][j]==3 && i==k-2 && (l==j-2 || l==j+2)) {
		if (b->data[(i+k)/2][(j+l)/2]==1 || b->data[(i+k)/2][(j+l)/2]==2) {
			changeBoard(b, i, j, 0);
			changeBoard(b, (i+k)/2, (j+l)/2, 0);
			changeBoard(b, k, l, 3);
			return 1;
		} else {
			return -1;
		}
	} else if (b->data[i][j]==4 && (i==k+2 || i==k-2) && (j==l-2 || j==l+2)) {
		if (b->data[(i+k)/2][(j+l)/2]==1 || b->data[(i+k)/2][(j+l)/2]==2) {
			changeBoard(b, i, j, 0);
			changeBoard(b, (i+k)/2, (j+l)/2, 0);
			changeBoard(b, k, l, 4);
			return 1;
		} else {
			return -1;
		}
	}
	return -1;
}

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

int notCapturable (int k, int l) {
	if (k<1 || l<1 || k>6 || l>6) {
		return 1;
	} else {
		return 0;
	}
}

void setAllBoardEmpty( struct board * b )
{	
	for (int i=0;i<8;i++){
		for (int j=0;j<8;j++){
			b->data[i][j] = 0;
		}
	}
}
