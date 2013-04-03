#ifndef CLIENT_H
#define CLIENT_H

#include "network_data.h"
#include "network.h"
#include "auth.h"
#include "list.h"
#include "filesystem.h"
#include "logic.h"
#include "interface.h"
#include "structs.h"

void evaluateParams(int argc, char * argv[]);
char * joinGame(struct client_network * net, struct clientuser * me);
int playGame(struct client_network * net, char * gameid, struct clientuser * me);

#endif
