#ifndef AUTH_H
#define AUTH_H

#include <stdlib.h>

struct user {
	int userid;
	int request;
	int game;
	int wins;
	int losses;
	char * username;
	char * password;
};

//standard header inclusion
char * generateLoginId(void);

#endif
