#include "network.h"

#define PORTNUM 2343

/*
 * Initiate a server netowork, listening for clients in PORTNUM
 */
void openServerNetwork(struct server_network * net)
{
	net->socksize = sizeof(struct sockaddr_in);
	
	memset(&net->serv, 0, sizeof(net->serv));
	
	net->serv.sin_family = AF_INET;         /* set the type of connection to TCP/IP */
	net->serv.sin_addr.s_addr = INADDR_ANY; /* set our address to any interface */
	net->serv.sin_port = htons(PORTNUM);    /* set the server port number */    
	
	net->mysocket = socket(AF_INET, SOCK_STREAM, 0);
	
	
	/* bind serv information to mysocket */
	bind(net->mysocket, (struct sockaddr *)&net->serv, sizeof(struct sockaddr));
	
	
	/* start listening, allowing a queue of up to 1 pending connection */
	listen(net->mysocket, 1);
	net->incoming = accept(net->mysocket, (struct sockaddr *)&net->dest, &net->socksize);
}

/*
 * Read a message received after server_network.incoming was triggered
 */
struct netmessage * readServerMessage(struct server_network * net)
{
	long len = recv(net->incoming, net->buffer, sizeof(net->buffer), 0);
	net->buffer[len] = '\0';
	
	return (struct netmessage *) net->buffer;
}

/*
 * Send a message over the network to a client
 */
void sendServerMessage(struct server_network * net, char * message)
{
	send(net->incoming, message, strlen(message), 0); 
	net->incoming = accept(net->mysocket, (struct sockaddr *)&net->dest, &net->socksize);
}

/*
 * Close an opened server network.
 */
void closeServerNetwork(struct server_network * net)
{
	close(net->incoming);
	close(net->mysocket);
}

