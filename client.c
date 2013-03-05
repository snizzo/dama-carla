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
 
#define MAXRCVLEN 500
#define PORTNUM 2343
 
int main()
{
	/*
	struct netmessage msg;
	setNetMessage(&msg, "ciao", "pippo", "", "", "");
	
	char * message = (char *) &msg;
	*/
	
	char message[] = "test message";
	
	char buffer[MAXRCVLEN + 1]; /* +1 so we can add null terminator */
	int mysocket;
	long len;
	struct sockaddr_in dest;
 
	mysocket = socket(AF_INET, SOCK_STREAM, 0);
 
	memset(&dest, 0, sizeof(dest));                /* zero the struct */
	dest.sin_family = AF_INET;
	dest.sin_addr.s_addr = inet_addr("127.0.0.1"); /* set destination IP number */
	dest.sin_port = htons(PORTNUM);                /* set destination port number */
 
	connect(mysocket, (struct sockaddr *)&dest, sizeof(struct sockaddr));
	
	if(send(mysocket, message, strlen(message), 0)<0){
		printf("error sending message\n");
	}
	
	len = recv(mysocket, buffer, MAXRCVLEN, 0);
 
	/* We have to null terminate the received data ourselves */
	buffer[len] = '\0';
 
	printf("Received %s (%ld bytes).\n", buffer, len);
 
	close(mysocket);
	return EXIT_SUCCESS;
}
