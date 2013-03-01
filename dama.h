#ifndef DAMA_H
#define DAMA_H

struct netmessage{
	char cmd1[50];
	char cmd2[50];
	char cmd3[50];
	char cmd4[50];
	char cmd5[50];
	char cmd6[50];
	char cmd7[50];
	char cmd8[50];
	char cmd9[50];
	char cmd10[50];
};

/*
 * A complete game is made of a board and 2 players.
 * This data structure should contain all the needed info about a game.
 * 
 * Server keeps track of everything while receiving updates from client and
 * updating their data structure.
 */

struct player{
	//nickname of registered player
	char nickname;
	//password of registered player
	char password;
	//id of registered player
	int id;
	//current color in use
	// 0: not in game
	// 1: white
	// 2: black
	int color;
	//total won games
	int won;
	//total lost games
	int lost;
	//win/lose ratio
	double wlr;
};

struct board{
	//board values
	// 'wf': white and free
	// 'bf': black and free
	//
	// 'ww': white occupied by a white pawn
	// 'wb': white occupied by a black pawn
	// 'bw': black occupied by a white pawn
	// 'bb': black occupied by a black pawn
	char grid[8][8];
};

struct game{
	struct board b;
	struct player white;
	struct player black;
	int wonby;
};
#endif
