#include <stdio.h>
#include <stdlib.h>

//specific lib inclusion
#include "network_data.h"
#include "network.h"
#include "auth.h"
#include "list.h"
#include "filesystem.h"
#include "logic.h"
#include "interface.h"
#include "client.h"

int main()
{
	
	struct client_network net;
	
	struct clientuser * me = malloc(sizeof(struct clientuser));
	me->logged = 0;
	
	setInterface(); //setting our program to use ncurses
	
	while(!me->logged){
		struct logininfo * logindata = NULL;
		
		logindata = showLoginForm(); //show login form
		
		singleWindowMessage("logging...");
		
		
		fullClientCommand(&net, "login", logindata->username, logindata->password, "", ""); //TODO: fixme
		
		//fullClientCommand(&net, "login", logindata->username, logindata->password, "", ""); //TODO: fixme
		
		struct netmessage * incoming = readClientMessage(&net);
		
		if (areEqual(incoming->msg1, "done")){
			singleWindowMessage("logged!");
			
			// set up base client user account
			me->username = copystring(logindata->username);
			me->password = copystring(logindata->password);
			me->loginkey = copystring(incoming->msg2);
			me->currentgame = NULL;
			me->logged = 1;
			me->wins = 0;
			me->losses = 0;
			
			sleep(2); //let the user read this
		} else if(areEqual(incoming->msg1, "wrongpassword")) {
			singleWindowMessage("Wrong Password!");
			sleep(2); //let the user read this
		} else if(areEqual(incoming->msg1, "usernotfound")) {
			singleWindowMessage("User Not Found!");
			sleep(2); //let the user read this
		} else {
			singleWindowMessage("Unknown Error!");
			sleep(2); //let the user read this
		}
		
		free(logindata->username);
		free(logindata->password);
		free(logindata);
		
	}
	
	unsetInterface(); //unset ncurses
	
/*	
	struct board b;
	
	
	struct client_network net;
	
	//login
	struct netmessage message;
	setNetMessage(&message, "login", "snizzo", "mypwd", "", "");
	
	sendClientMessage(&net, &message);
	
	struct netmessage * incoming = readClientMessage(&net);
	
	printf("%s\n", incoming->msg1);
	printf("%s\n", incoming->msg2);
	printf("%s\n", incoming->msg3);
	printf("%s\n", incoming->msg4);
	printf("%s\n", incoming->msg5);
	
	
	sleep(2);
	
	char * loginkey = copystring(incoming->msg2);
	
	//authping, incoming->msg2 contains the authentication key
	setNetMessage(&message, "authping", "", "", "", loginkey);
	
	sendClientMessage(&net, &message);
	
	incoming = readClientMessage(&net);
	
	printf("%s\n", incoming->msg1);
	printf("%s\n", incoming->msg2);
	printf("%s\n", incoming->msg3);
	printf("%s\n", incoming->msg4);
	printf("%s\n", incoming->msg5);
	

	initscr();
	mvprintw(0, 0,"Nord-ovest"); 
	mvprintw(LINES-1, 0,"Sud-ovest");
	mvprintw(0, COLS-8,"Nord-est"); 
	mvprintw(LINES-1, COLS-7,"Sud-est");
	
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_WHITE);
	init_pair(2, COLOR_WHITE, COLOR_BLACK);
	init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(4, COLOR_BLACK, COLOR_BLACK);
	
	b.data[0][7] = 3;
	b.data[0][5] = 3;
	b.data[0][3] = 3;
	b.data[0][1] = 0;
	
	b.data[1][6] = 2;
	b.data[1][4] = 4;
	b.data[1][2] = 4;
	b.data[1][0] = 0;
	
	b.data[2][7] = 0;
	b.data[2][5] = 3;
	b.data[2][3] = 3;
	b.data[2][1] = 0;
	
	b.data[7][6] = 0;
	b.data[7][4] = 1;
	b.data[7][2] = 0;
	b.data[7][0] = 1;
	
	b.data[5][6] = 1;
	b.data[5][4] = 2;
	b.data[5][2] = 1;
	b.data[5][0] = 0;
	
	b.data[6][7] = 0;
	b.data[6][5] = 1;
	b.data[6][3] = 1;
	b.data[6][1] = 0;
	
	for (int i=0;i<8;i++){
			for (int j=0;j<8;j++){
				if (even(i+j)) {
					attron(COLOR_PAIR(1));
					mvprintw(i, j, "e");
				} else if (b.data[i][j]==1) {
					attron(COLOR_PAIR(2));
					mvprintw(i, j, "@");
				} else if (b.data[i][j]==2) {
					attron(COLOR_PAIR(2));
					mvprintw(i, j, "W");
				} else if (b.data[i][j]==3) {
					attron(COLOR_PAIR(3));
					mvprintw(i, j, "@");
				} else if (b.data[i][j]==4) {
					attron(COLOR_PAIR(3));
					mvprintw(i, j, "W");
				} else {
					attron(COLOR_PAIR(4));
					mvprintw(i, j, "e");
				}
			}
		}
				

	refresh();  
	getch();  
	endwin(); 
*/	
	return 0;
}


//various utils
int even(int n) {
	if ((n % 2)==0) {
		return 1;
	} else {
		return 0;
	}
}

