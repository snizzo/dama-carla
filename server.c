#include <stdio.h>
#include <stdlib.h>

//specific lib inclusion
#include "network_data.h"
#include "network.h"
#include "filesystem.h"


int main()
{
	
	
	saveRecord("config", "matrioska", "bubua");
	readRecord("config", "barabba");
	
	//initializing server network
	struct server_network net;
	openServerNetwork(&net);
	
	while(net.incoming)
	{
		struct netmessage * message = readServerMessage(&net);
		
		
		
		printf("%s\n", message->msg1);
		
		printf("Incoming connection.\n");
		
		struct netmessage response;
		setNetMessage(&response, "risp", "rispostella", "rispostuzz", "", "rispostinax");
		
		sendServerMessage(&net, &response);
	}
	
	closeServerNetwork(&net);
	
	return EXIT_SUCCESS;
}
