#ifndef AUTH_H
#define AUTH_H

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
};

//standard header inclusion
char * generateLoginId(void);
struct user * createUser(int wins, int losses, char * gameid, char * key, char * username, char * password);
struct game * createGame(char * key, char * white, char * black);
char * copystring(char * str);
char * trimwhitespace(char *str);
#endif
