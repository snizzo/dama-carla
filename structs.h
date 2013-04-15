#ifndef STRUCTS_H
#define STRUCTS_H

struct user {
	int wins;
	int losses;
	char * gameid;
	char * key;
	char * username;
	char * password;
};

struct game {
	char * key;
	char * white;
	char * black;
	/*
	 * 1: white turn
	 * 2: black turn
	 * 3: white win
	 * 4: black win
	 */
	char * lastmove;
	int status;
};

struct board{
	int data[8][8];
};

struct clientuser {
	char * loginkey;
	char * username;
	char * password;
	char * currentgame;
	int logged;
	int wins;
	int losses;
};

struct moveinfo{
	char * daC;
	char * daL;
	char * aC;
	char * aL;
};

struct token {
	char key[100];
	char value[100];
};

struct logininfo{
	char * username;
	char * password;
};

union data{
	struct user * u;
	struct game * g;
};

struct lnode {
	union data d;
	struct lnode * next;
};

struct llist{
	struct lnode * first;
};

#endif
