#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "network.h"

void manageSecondParams(int argc, char *argv[]);

int main(int argc,char* argv[])
{

    struct clientinfo info;

    manageSecondParams(argc,argv);

    initiateNetwork(&info.net,argv[1],atoi(argv[2]));
    //opening socket
    //info.net.socketDescriptor = createSocket(argv[1],atoi(argv[2]));

    sendMessageAndWaitReply(&info.net, argv[3]);
	
    printf("DEBUG: server reply: %s \n", info.net.buffer);

	//Chiudo il socket.
    closeMessage(info.net.socketDescriptor);

	return 0;
}


void manageSecondParams(int argc, char *argv[])
{
    //checking if client was launched to print help
    if ( (argc==2) && (strcmp(argv[1],"--help")==0) ){
        printf("Usage: %s [ip address] [port] [command]\n\n", argv[0]);

        //close without errors
        exit(0);
    }
}
