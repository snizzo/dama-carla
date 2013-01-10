#ifndef NETWORK_H
#define NETWORK_H
//here goes my header

void closeMessage(int sock);

int createSocket(char* destination, int port);

void sendMessage(int sock, char* message);

#endif
