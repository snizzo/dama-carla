#include "auth.h"

/*
 * This function generates a unique hash to give at a client.
 * Server will remember of the client thanks to this hash. In order
 * to increase security, this should be quite big.
 */
char * generateLoginId()
{
	int len = 30;
	
	char * key = malloc(sizeof(char)* (unsigned long) len+1);
	
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < len; ++i) {
        key[i] = alphanum[(unsigned long) rand() % (sizeof(alphanum) - 1)];
    }

    key[len] = 0;
    
    return key;
}

char * copystring(char * str)
{
	char * copied = malloc(sizeof(char)*strlen(str));
	strcpy(copied,str);
	return copied;
}

struct user * createUser(int wins, int losses, char * gameid, char * key, char * username, char * password)
{
	struct user * u = malloc(sizeof(struct user)*1);
	u->wins = wins;
	u->losses = losses;
	u->gameid = gameid;
	u->key = key;
	u->username = username;
	u->password = password;
	
	return u;
}
