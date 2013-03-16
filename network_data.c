#include "network_data.h"

void setNetMessage(struct netmessage * net, char * cmd1, char * cmd2, char * cmd3, char * cmd4, char * cmd5)
{
	strcpy(net->msg1, cmd1);
	strcpy(net->msg2, cmd2);
	strcpy(net->msg3, cmd3);
	strcpy(net->msg4, cmd4);
	strcpy(net->msg5, cmd5);
	
	return;
}
