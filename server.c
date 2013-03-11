#include <stdio.h>
#include <stdlib.h>

//specific lib inclusion
#include "network_data.h"
#include "network.h"
#include "filesystem.h"

int main()
{	
	
	//initializing server network
	struct server_network net;
	openServerNetwork(&net);
	
	while(net.incoming)
	{
		struct netmessage * message = readServerMessage(&net);
		
		// COMMAND: PING
		if (areEqual("ping", message->msg1)) {
			singleCommand(&net, "pong");
			
		// COMMAND: REGISTER <nickname> <password>
		} else if (areEqual("register", message->msg1)) {
			if(!isPresentRecord("users", message->msg2)){
				saveRecord("users", message->msg2, message->msg3);
				
				singleCommand(&net, "done");
			} else {
				singleCommand(&net, "useralreadythere");
			}
			
			
		// COMMAND: <unknown>
		} else {
			singleCommand(&net, "commandnotfound");
		}
		
	}
	
	closeServerNetwork(&net);
	
	return EXIT_SUCCESS;
}
