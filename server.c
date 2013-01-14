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
#include "parser.h"

int main()
{

    struct serverinfo info;

    char * cmd;

    initiateServerNetwork(&info.net, 1745);

    //accepting and managing events
    while(1){
        if (acceptServerMessage(&info.net)){

            cmd = strtok(info.net.buffer, " ");

            //single ping alive command
            if(strcmp(&cmd[0],"ping")==0){
                cmd = strtok (NULL, " ");
                printf("ci siamo\n");
                if(cmd!=NULL){
                    printf("non null\n");
                    if(strcmp(&cmd[0],"one")==0){
                        sendMessage(info.net.newSocket, "one received");
                    }else if(strcmp(&cmd[0],"two")==0){
                        sendMessage(info.net.newSocket, "two received");
                    } else {
                        sendMessage(info.net.newSocket, "needed a second parameter <param>");
                    }
                }
            }

            //remote shutdown command
            if(strcmp(&cmd[0],"exit")==0){
                return 0;
            }

            //closing temporary socket
            close(info.net.newSocket);
            //setting pointer to null
            cmd = NULL;
        }

    }

	//Chiusura del socket
    closeNetwork(&info.net);
    printf("Server quitting...\n");

	return 0;
}
