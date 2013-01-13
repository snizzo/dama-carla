#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
//"in" per "sockaddr_in"
#include <netinet/in.h>
//"netdb" per "gethostbyname"
#include <netdb.h>
#include <fcntl.h>
#include"network.h"

/*
 * Initialize the socket used for client/server communications.
 *
 * @param struct networkinfo *net   Struct containing all the network data.
 * @param char *addr                Target address to connect
 * @param int port                  Target port to connect
 *
 */
void initiateNetwork(struct networkinfo *net, char *addr, int port)
{
    net->socketDescriptor = createSocket(addr,port);
    net->exitCond = 0;
}

void closeMessage(int sock)
{
    close(sock);
    return;
}

int createSocket(char* destination, int port)
{
    struct sockaddr_in temp;
    struct hostent *h;
    int sock;
    int errore;

    //Tipo di indirizzo
    temp.sin_family=AF_INET;
    temp.sin_port=htons(port);
    h=gethostbyname(destination);
    if (h==0)
    {
        printf("Gethostbyname failed\n");
        exit(1);
    }
    memcpy(h->h_addr,&temp.sin_addr,h->h_length);
    //Creazione socket.
    sock=socket(AF_INET,SOCK_STREAM,0);
    //Connessione del socket. Esaminare errore per compiere azioni
    //opportune in caso di errore.
    errore=connect(sock, (struct sockaddr*) &temp, sizeof(temp));
    return sock;
}

int createServerSocket(int port)
{
    int sock,errore;
    struct sockaddr_in temp;

    //Creazione socket
    sock=socket(AF_INET,SOCK_STREAM,0);
    //Tipo di indirizzo
    temp.sin_family=AF_INET;
    temp.sin_addr.s_addr=INADDR_ANY;
    temp.sin_port=htons(port);

    //Il socket deve essere non bloccante
    errore=fcntl(sock,F_SETFL,O_NONBLOCK);

    //Bind del socket
    errore=bind(sock,(struct sockaddr*) &temp,sizeof(temp));
    //Per esempio, facciamo accettare fino a 7 richieste di servizio
    //contemporanee (che finiranno nella coda delle connessioni).
    errore=listen(sock,7);

    return sock;
}

void sendMessage(int sock, char* message)
{
    printf("Client: %s\n",message);
    //Si puo' notare il semplice utilizzo di write:
    //write(socket, messaggio, lunghezza messaggio)
    if (write(sock,message,strlen(message))<0)
    {
        printf("ERROR: Unable to send the message.\n");
        closeMessage(sock);
        exit(1);
    }
    return;
}

/*
 * Modifies the struct network info inserting the message into buffer.
 */
void sendMessageAndWaitReply(struct networkinfo *net, char *message)
{
    sendMessage(net->socketDescriptor,message);

    //event retrival
    while (!net->exitCond)
    {
        //Lettura dei dati dal socket (messaggio ricevuto)
        if ((net->howMany=read(net->socketDescriptor,net->buffer,sizeof(net->buffer)))>0)
        {
            //Aggiusto la lunghezza...
            net->buffer[net->howMany]=0;
            net->exitCond = 1;
        }
    }
}
