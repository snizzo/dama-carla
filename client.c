#include "network.h"

int main(int argc,char* argv[])
{
    char buffer[512];
    int socketDescriptor,newSocket;
	int exitCond=0;
    int howMany;

    //checking if client was launched to print help
    if ( (argc==2) && (strcmp(argv[1],"--help")==0) ){
        printf("Usage: %s [ip address] [port] [command]\n\n", argv[0]);

        //close without errors
        exit(0);
    }
	
	//Creo e connetto il socket
    socketDescriptor=createSocket(argv[1],atoi(argv[2]));
	
	//Spedisco il messaggio voluto
    if ((argc==2)&&(strcmp(argv[3],"exit")==0)) {
        sendMessage(socketDescriptor,"exit");
    } else {
        sendMessage(socketDescriptor,argv[3]);
    }
	
	while (!exitCond)
	{
		//Lettura dei dati dal socket (messaggio ricevuto)
        if ((howMany=read(socketDescriptor,buffer,sizeof(buffer)))>0)
		{
			//Aggiusto la lunghezza...
            buffer[howMany]=0;
			//Elaborazione dati ricevuti
			
			printf("Server response: %s \n", buffer);
			exitCond = 1;
		}
	}
	
	//Chiudo il socket.
    closeMessage(socketDescriptor);

	return 0;
}
