#ifndef AUTH_H
#define AUTH_H

#include <stdlib.h>

struct user {
	int id;
	int request;
	int game;
	int wins;
	int losses;
	char * username;
	char * password;
};

struct game {
	int id;
	char * white;
	char * black;
};

//standard header inclusion
char * generateLoginId(void);

#endif
