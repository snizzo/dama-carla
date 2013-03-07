#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

//specific liib inclusion
#include "network_data.h"
#include "network.h"


int main()
{	
	//initializing server network
	struct server_network net;
	openServerNetwork(&net);
	
	while(net.incoming)
	{
		struct netmessage * message = readServerMessage(&net);
		
		printf("%s\n", message->msg1);
		printf("%s\n", message->msg2);
		printf("%s\n", message->msg3);
		printf("%s\n", message->msg4);
		printf("%s\n", message->msg5);
		
		printf("Incoming connection.\n");
		
		sendServerMessage(&net, "barabba e strafiquo :)");
	}
	
	closeServerNetwork(&net);
	
	return EXIT_SUCCESS;
}
