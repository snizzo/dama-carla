#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "network.h"
#include "dama.h"

void manageSecondParams(int argc, char *argv[]);

int main(int argc,char* argv[])
{

    struct clientinfo info;

    manageSecondParams(argc,argv);

    initiateNetwork(&info.net,argv[1],atoi(argv[2]));
    //opening socket
    //info.net.socketDescriptor = createSocket(argv[1],atoi(argv[2]));
	
	struct netmessage message;
	strcpy(message.cmd1, "register");
	strcpy(message.cmd2, "snizzo");
	strcpy(message.cmd3, "maddaffacca");
	
	char * message_pointer = (char *) &message;
	
    sendMessageAndWaitReply(&info.net, message_pointer);
    
    printf("srv: %s \n", info.net.buffer);
    
	strcpy(message.cmd1, "register");
	strcpy(message.cmd2, "maramao");
	strcpy(message.cmd3, "merdacane");
	
    sendMessageAndWaitReply(&info.net, message_pointer);
    
    printf("srv: %s \n", info.net.buffer);

    //close socket
    closeNetwork(&info.net);

	return 0;
}


void manageSecondParams(int argc, char *argv[])
{
    //checking if client was launched to print help
    if ( (argc==2) && (strcmp(argv[1],"--help")==0) ){
        printf("Usage: %s [ip address] [port] [command]\n\n", argv[0]);
		
	}
    if ( (argc==2) && (strcmp(argv[1],"--credit")==0) ){
        printf("Usage: small dama game made by voldemort and sauron\n\n");
    }
    
	//close without errors
	exit(0);
}
