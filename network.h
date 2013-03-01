#ifndef NETWORK_H
#define NETWORK_H
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
//"in" per "sockaddr_in"
#include <netinet/in.h>
//"netdb" per "gethostbyname"
#include <netdb.h>
#include <fcntl.h>
//here goes my header

struct networkinfo{
    char buffer[512];
    int socketDescriptor,newSocket;
    int exitCond;
    int howMany;
};

struct clientinfo{
    struct networkinfo net;
};

struct serverinfo{
    struct networkinfo net;
};


void initiateServerNetwork(struct networkinfo *net, int port);

int acceptServerMessage(struct networkinfo *net);

void initiateNetwork(struct networkinfo *net, char *addr, int port);

void closeNetwork(struct networkinfo *net);

int createSocket(char* destination, int port);

int createServerSocket(int port);

void sendMessage(int sock, char* message);

void sendMessageAndWaitReply(struct networkinfo *net, char *message);

#endif
