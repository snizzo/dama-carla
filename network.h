#ifndef NETWORK_H
#define NETWORK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include "network_data.h"

struct server_network{
	struct sockaddr_in dest;         /* socket info about the machine connecting to us */
	struct sockaddr_in serv;         /* socket info about our server */
	int mysocket, incoming;    /* socket used to listen for incoming connections */
	socklen_t socksize;              /*  = sizeof(struct sockaddr_in) */
	char buffer[300];                /* buffer for incoming messages */
};


//function prototypes of network.c
void openServerNetwork(struct server_network * net);
struct netmessage * readServerMessage(struct server_network * net);
void sendServerMessage(struct server_network * net, char * message);
void closeServerNetwork(struct server_network * net);

#endif
