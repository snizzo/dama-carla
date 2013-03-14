#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

//specific lib inclusion
#include "network_data.h"
#include "network.h"
#include "auth.h"
 
int main()
{
	
	
	
	struct client_network net;
	
	struct netmessage message;
	setNetMessage(&message, "login", "snizzo", "mypwd", "", "");
	
	sendClientMessage(&net, &message);
	
	struct netmessage * incoming = readClientMessage(&net);
	
	printf("%s\n", incoming->msg1);
	printf("%s\n", incoming->msg2);
	printf("%s\n", incoming->msg3);
	printf("%s\n", incoming->msg4);
	printf("%s\n", incoming->msg5);
	
	/*
	initscr();
	mvprintw(0, 0,"Nord-ovest"); 
	mvprintw(LINES-1, 0,"Sud-ovest");
	mvprintw(0, COLS-8,"Nord-est"); 
	mvprintw(LINES-1, COLS-7,"Sud-est");

	refresh();  
	getch();  
	endwin(); 
	*/
	return 0;
}
