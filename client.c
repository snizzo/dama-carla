#include <stdio.h>
#include <stdlib.h>

//specific lib inclusion
#include "network_data.h"
#include "network.h"
#include "auth.h"
 
int main()
{
	
	struct client_network net;
	
	struct netmessage message;
	setNetMessage(&message, "login", "snizzo", "mypwid", "", "");
	
	sendClientMessage(&net, &message);
	
	struct netmessage * incoming = readClientMessage(&net);
	
	printf("%s\n", incoming->msg1);
	printf("%s\n", incoming->msg2);
	printf("%s\n", incoming->msg3);
	printf("%s\n", incoming->msg4);
	printf("%s\n", incoming->msg5);
	
	
	return 0;
}
