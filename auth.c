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
