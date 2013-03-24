#ifndef CLIENT_H
#define CLIENT_H

struct clientuser {
	char * loginkey;
	char * username;
	char * password;
	char * currentgame;
	int logged;
	int wins;
	int losses;
};

int even(int n);

#endif
