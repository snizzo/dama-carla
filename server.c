#include <stdio.h>
#include <stdlib.h>

//specific lib inclusion
#include "network_data.h"
#include "network.h"
#include "filesystem.h"

int areEqual(char * s1, char * s2);

int main()
{
	
	
	
	//initializing server network
	struct server_network net;
	openServerNetwork(&net);
	
	while(net.incoming)
	{
		struct netmessage * message = readServerMessage(&net);
		
		if (areEqual("ping", message->msg1)) {
			struct netmessage response;
			setNetMessage(&response, "pong", "", "", "", "");
			sendServerMessage(&net, &response);
		} else {
			struct netmessage response;
			setNetMessage(&response, "nope", "", "", "", "");
			sendServerMessage(&net, &response);
		}
		
		printf("%s\n", message->msg1);
		
		printf("Incoming connection.\n");
	}
	
	closeServerNetwork(&net);
	
	return EXIT_SUCCESS;
}

int areEqual(char * s1, char * s2)
{
	if (strcmp(s1, s2)==0){
		return 1;
	}
}
