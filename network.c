#include "network.h"

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

void initiateServerNetwork(struct networkinfo *net, int port)
{
    net->socketDescriptor = createServerSocket(port);
    net->exitCond = 0;
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
    if(errore<0){
		printf("ERROR: connection to server refused.");
		close(sock);
		exit(1);
	}
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
    errore=fcntl(sock,F_SETFL);

    //Bind del socket
    errore=bind(sock,(struct sockaddr*) &temp,sizeof(temp));
    //Per esempio, facciamo accettare fino a 7 richieste di servizio
    //contemporanee (che finiranno nella coda delle connessioni).
    errore=listen(sock,7);

    return sock;
}

void sendMessage(int sock, char* message)
{
    //Si puo' notare il semplice utilizzo di write:
    //write(socket, messaggio, lunghezza messaggio)
    ssize_t w = write(sock,message,500);
    //printf("%d\n", w);
    if (w<0)
    {
        printf("ERROR: Unable to send the message.\n");
        close(sock);
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
    //printf("diocane");

    //event retrival
    while (!net->exitCond)
    {
        //Lettura dei dati dal socket (messaggio ricevuto)
        if ((net->howMany=read(net->socketDescriptor,net->buffer,sizeof(net->buffer)))>0)
        {
            //Aggiusto la lunghezza...
            net->buffer[net->howMany]='\0';
            net->exitCond = 1;
        }
    }
}

/*
 * Interface for accepting server events
 */
int acceptServerMessage(struct networkinfo *net)
{
        //Test sul socket: accept non blocca, ma il ciclo while continua
        //l'esecuzione fino all'arrivo di una connessione.
        if ((net->newSocket=accept(net->socketDescriptor,0,0))!=-1)
        {
            //Lettura dei dati dal socket (messaggio ricevuto)
            if ((net->howMany=read(net->newSocket,net->buffer,sizeof(net->buffer)))<0)
            {
                 printf("Impossibile leggere il messaggio.\n");
                 close(net->newSocket);
            }
            else
            {
                //Aggiusto la lunghezza...
                net->buffer[net->howMany]=0;

                return 1;

            }
        }
        return 0;
}

void closeNetwork(struct networkinfo *net)
{
    close(net->socketDescriptor);
}
