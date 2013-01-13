#ifndef NETWORK_H
#define NETWORK_H
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

void initiateNetwork(struct networkinfo *net, char *addr, int port);

void closeMessage(int sock);

int createSocket(char* destination, int port);

int createServerSocket(int port);

void sendMessage(int sock, char* message);

void sendMessageAndWaitReply(struct networkinfo *net, char *message);

#endif
