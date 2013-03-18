/*
   CLIENT LIB USAGE:
   
   This network is structured as a call-response system. This means you have
   to query server with a netmessage like this:
  
   struct netmessage message;
	setNetMessage(&message, "register", "snizzo", "mypwd", "", "");
	
	sendClientMessage(&net, &message);
   
   then, you have to instantly call the read message function like this:
   
   struct netmessage * incoming = readClientMessage(&net);
   
   and you will have all the message mapped to incoming netmessage. 
   
   
   
 */

#include "network.h"

#define PORTNUM 2343
#define TARGET_IP "127.0.0.1"

/*
 * Initiate a server network, listening for clients in PORTNUM
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
void sendServerMessage(struct server_network * net, struct netmessage * message)
{
	char * c = (char *) message;
	send(net->incoming, c, 250, 0);
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

//client ----------------------------------------------------------------------

/*
 * Set up a client network environment.
 */
void openClientNetwork(struct client_network * net) {
	net->mysocket = socket(AF_INET, SOCK_STREAM, 0);
 
	memset(&net->dest, 0, sizeof(net->dest));                /* zero the struct */
	net->dest.sin_family = AF_INET;
	net->dest.sin_addr.s_addr = inet_addr(TARGET_IP); /* set destination IP number */
	net->dest.sin_port = htons(PORTNUM);                /* set destination port number */
 
	connect(net->mysocket, (struct sockaddr *)&net->dest, sizeof(struct sockaddr));
}

/*
 * send a struct netmessage from client to server
 */
void sendClientMessage(struct client_network * net, struct netmessage * message)
{
	openClientNetwork(net);
	
	char * decoded_message = (char *) message;
	if(send(net->mysocket, decoded_message, 250, 0)<0){
		printf("error sending message!\n");
	}
}

/*
 * read a message from server to client
 */
struct netmessage * readClientMessage(struct client_network * net)
{
	long len = recv(net->mysocket, net->buffer, sizeof(net->buffer), 0);
 
	/* We have to null terminate the received data ourselves */
	net->buffer[len] = '\0';
	
	close(net->mysocket); //close client network part
	
	return (struct netmessage *) net->buffer;
}

//utils--------------------------------------------------------------
void singleCommand(struct server_network * net, char * cmd)
{
	struct netmessage response;
	setNetMessage(&response, cmd, "", "", "", "");
	sendServerMessage(net, &response);
}

void fullCommand(struct server_network * net, char * cmd1, char * cmd2, char * cmd3, char * cmd4, char * cmd5)
{
	struct netmessage response;
	setNetMessage(&response, cmd1, cmd2, cmd3, cmd4, cmd5);
	sendServerMessage(net, &response);
}

int areEqual(char * s1, char * s2)
{
	if (strcmp(s1, s2)==0){
		return 1;
	} else {
		return 0;
	}
}
