#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
//"in" per "sockaddr_in"
#include <netinet/in.h>
//"fcntl" per la funzione "fcntl"
#include <fcntl.h>

#include "network.h"

int main()
{

    struct serverinfo info;

    initiateServerNetwork(&info.net, 1745);

    //accepting and managing events
    while(1){
        if (acceptServerMessage(&info.net)){
            //single ping alive command
            if(strcmp(info.net.buffer,"ping")==0){
                sendMessage(info.net.newSocket, "pong");
            }

            //remote shutdown command
            if(strcmp(info.net.buffer,"exit")==0){
                return 0;
            }
            //Chiusura del socket temporaneo
            close(info.net.newSocket);
        }

    }

	//Chiusura del socket
    closeNetwork(&info.net);
    printf("Server quitting...\n");

	return 0;
}
