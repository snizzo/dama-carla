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
	//N.B. L'esempio non usa la funzione fork per far vedere l'utilizzo di
	//     socket non bloccanti
	char  buffer[512];
    int socketDescriptor, newSocket;
	int exitCond=0;
    int howMany;
	
    socketDescriptor=createServerSocket(1745);
	printf("Server: Attendo connessioni...\n");
	while (!exitCond)
	{
		//Test sul socket: accept non blocca, ma il ciclo while continua
		//l'esecuzione fino all'arrivo di una connessione.
        if ((newSocket=accept(socketDescriptor,0,0))!=-1)
		{
			//Lettura dei dati dal socket (messaggio ricevuto)
            if ((howMany=read(newSocket,buffer,sizeof(buffer)))<0)
			{
				 printf("Impossibile leggere il messaggio.\n");
                 closeMessage(newSocket);
			}
			else
			{
				//Aggiusto la lunghezza...
                buffer[howMany]=0;
				//Elaborazione dati ricevuti
				
				//"exit" case
				if (strcmp(buffer,"exit")==0){
					exitCond=1;
				}

				if (strcmp(buffer,"ping")==0){
                    sendMessage(newSocket,"pong");
				}
			}
			//Chiusura del socket temporaneo
            closeMessage(newSocket);
		}
	}
	//Chiusura del socket
    closeMessage(socketDescriptor);
    printf("Server quitting...\n");

	return 0;
}
