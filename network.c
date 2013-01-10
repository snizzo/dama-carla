#include <sys/types.h>
#include <sys/socket.h>
//"in" per "sockaddr_in"
#include <netinet/in.h>
//"netdb" per "gethostbyname"
#include <netdb.h>

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
    bcopy(h->h_addr,&temp.sin_addr,h->h_length);
    //Creazione socket.
    sock=socket(AF_INET,SOCK_STREAM,0);
    //Connessione del socket. Esaminare errore per compiere azioni
    //opportune in caso di errore.
    errore=connect(sock, (struct sockaddr*) &temp, sizeof(temp));
    return sock;
}

void sendMessage(int sock, char* message)
{
    printf("Client: %s\n",message);
    //Si puo' notare il semplice utilizzo di write:
    //write(socket, messaggio, lunghezza messaggio)
    if (write(sock,message,strlen(message))<0)
    {
        printf("Unable to send the message.\n");
        closeMessage(sock);
        exit(1);
    }
    printf("Message delivered successfully.\n");
    return;
}
