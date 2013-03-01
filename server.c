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
#include "filesystem.h"
#include "serverevents.h"
#include "dama.h"

int main()
{

	struct serverinfo info;
	
	initiateServerNetwork(&info.net, 1745);
	
    //accepting and managing events
    while(1){
        if (acceptServerMessage(&info.net)){
			
			// info.net.buffer
			struct netmessage * message = (struct netmessage *) info.net.buffer;
			
			//single ping alive command
			//printf("%s\n", message->cmd1);
            if(strcmp(message->cmd1,"register")==0){
				registerNewPlayer(message->cmd2, message->cmd3);
				
				sendMessage(info.net.newSocket, "done");
            }
			
            //single ping alive command
            if(strcmp(info.net.buffer,"ping")==0){
                sendMessage(info.net.newSocket, "infosrv pong");
            }

            //remote shutdown command
            if(strcmp(info.net.buffer,"exit")==0){
				sendMessage(info.net.newSocket, "infosrv shutdown");
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
