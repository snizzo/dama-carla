#ifndef NETWORK_DATA_H
#define NETWORK_DATA_H
#include <string.h>

struct netmessage {
	char msg1[50];
	char msg2[50];
	char msg3[50];
	char msg4[50];
	char msg5[50];
};

void setNetMessage(struct netmessage * net, char * cmd1, char * cmd2, char * cmd3, char * cmd4, char * cmd5);

#endif
