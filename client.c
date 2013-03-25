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

void evaluateParams(int argc, char * argv[]);
int setBox(struct board * b);
int even(int n);

int main(int argc, char * argv[])
{
	
	//evaluating additional parameters
	evaluateParams(argc,argv);
	
	//initializing client network
	struct client_network net;
	
	//creating the user structure that will take record of the user info and current state
	struct clientuser * me = malloc(sizeof(struct clientuser));
	me->logged = 0;
	
	setInterface(); //setting our program to use ncurses
	while(true){
		//anonymous play not supported - force user to log in
		while(!me->logged){
			struct logininfo * logindata = NULL;
			
			logindata = showLoginForm(); //show login form, login data is allocated, needs to be free
			
			singleWindowMessage("logging...");
			
			
			fullClientCommand(&net, "login", logindata->username, logindata->password, "", "");
			
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
				
				sleep(2);
			} else if(areEqual(incoming->msg1, "wrongpassword")) {
				singleWindowMessage("Wrong Password!");
				sleep(2);
				
			} else if(areEqual(incoming->msg1, "usernotfound")) {
				singleWindowMessage("User Not Found!");
				sleep(2);
				
			} else {
				singleWindowMessage("Unknown Error!");
				sleep(2);
				
			}
			
			free(logindata->username);
			free(logindata->password);
			free(logindata);
			
		}
		
		int choice = showMainMenu();
		
		switch (choice){
			case 0:
				fullClientCommand(&net, "logout","","","",me->loginkey);
				struct netmessage * incoming = readClientMessage(&net);
				if(areEqual(incoming->msg1, "done")){
					me->logged = 0;
					free(me->username);
					free(me->password);
					free(me->loginkey);
					me->currentgame = NULL;
				}
				break;
			case 1:
				break;
				//join game
		}
		
	}
	
	unsetInterface(); //unset ncurses
	
	return 0;
  
}

/*
 * Evaluate additional lauch parameters
 */
void evaluateParams(int argc, char * argv[])
{
	if ((argc>1) && (areEqual("--help", argv[1]))){
		printf("Dama Carla - Online Dama Client\n");
		printf("Port   : 2343\n");
		printf("Author : Claudio Desideri <happy.snizzo@gmail.com>\n");
		printf("Website: http://dama-carla.googlecode.com\n");
		printf("\n");
		printf("\n");
		printf("Usage:\n");
		printf("\n");
		printf("register <nickname> <password> :\n");
		printf("Register a new account on server with given <nickname> and <password>\n");
		exit(0);
	} else if ((argc>=4) && (areEqual("register", argv[1]))){
		//initializing client network
		struct client_network net;
		fullClientCommand(&net, "register", argv[2], argv[3], "", "");
		
		struct netmessage * incoming = readClientMessage(&net);
		if((areEqual(incoming->msg1,"done"))){
			printf("done\n");
			exit(0);
		} else if ((areEqual(incoming->msg1,"alreadythere"))) {
			printf("user already present in database\n");
			exit(0);
		} else {
			printf("unknown error :(\n");
			printf("feel free to report a bug to http://dama-carla.googlecode.com\n");
			exit(0);
		}
	}
}
	
/* qui inizia il mio codice xD (che funziona, se vuoi provarlo, basta togliere l'ultima parentesi prima di questa riga xD)
	 
	 struct board b;
	 
	 for (int i=0;i<8;i++){
		for (int j=0;j<8;j++){
			b.data[i][j] = 0;
		}
	}
	 
	 b.data[0][7] = 1;
	 b.data[0][5] = 1;
	 b.data[0][3] = 1;
	 b.data[0][1] = 1;
	 
	 b.data[1][6] = 2;
	 b.data[1][4] = 2;
	 b.data[1][2] = 2;
	 b.data[1][0] = 2;
	
	 b.data[2][7] = 1;
   	 b.data[2][5] = 1;
	 b.data[2][3] = 2;
	 b.data[2][1] = 2;
	
	 b.data[7][6] = 3;
	 b.data[7][4] = 3;
	 b.data[7][2] = 3;
	 b.data[7][0] = 3;
	
	 b.data[5][6] = 4;
	 b.data[5][4] = 4;
	 b.data[5][2] = 4;
	 b.data[5][0] = 4;
	
	 b.data[6][7] = 3;
	 b.data[6][5] = 3;
	 b.data[6][3] = 4;
	 b.data[6][1] = 4;
	 
	setBox(&b);
}

//various utils
int even(int n) {
	if ((n % 2)==0) {
		return 1;
	} else {
		return 0;
	}
}


	 
int setBox(struct board * b) {
	initscr(); 
	start_color();
	init_pair(1,COLOR_WHITE,COLOR_WHITE);
	init_pair(2,COLOR_WHITE,COLOR_BLACK);
	init_pair(3,COLOR_MAGENTA,COLOR_BLACK);
	for (int a=0; a<8; a++) {
		for (int c=0; c<8; c++) {
		 int k=a*3;
		 int l=c*5;
		 if (b->data[a][c]==1) {
			 attron(COLOR_PAIR(2));
			 for (int i=k; i<k+3; i++) {
				 for (int j=l; j<l+5; j++) {
					 mvprintw(i, j, " ");
				 }
			 }
			 mvprintw(k+1, l+2, "O");
		 } else if (b->data[a][c]==2) {
			 attron(COLOR_PAIR(2));
			 for (int i=k; i<k+3; i++) {
				 for (int j=l; j<l+5; j++) {
					 mvprintw(i, j, " ");
				 }
			 }
			 mvprintw(k+1, l+2, "@");
		 } else if (b->data[a][c]==3) {
			 attron(COLOR_PAIR(3));
			 for (int i=k; i<k+3; i++) {
				 for (int j=l; j<l+5; j++) {
					 mvprintw(i, j, " ");
				 }
			 }
			 mvprintw(k+1, l+2, "O");
		 } else if (b->data[a][c]==4) {
			 attron(COLOR_PAIR(3));
			 for (int i=k; i<k+3; i++) {
				 for (int j=l; j<l+5; j++) {
					 mvprintw(i, j, " ");
				 }
			 }
			 mvprintw(k+1, l+2, "@");
		 } else if (even(a+c)) {
			 attron(COLOR_PAIR(1));
			 for (int i=k; i<k+3; i++) {
				 for (int j=l; j<l+5; j++) {
					 mvprintw(i, j, " ");
				 }
			 }
		 } else {
			 attron(COLOR_PAIR(2));
			 for (int i=k; i<k+3; i++) {
				 for (int j=l; j<l+5; j++) {
					 mvprintw(i, j, " ");
				 }
			 }
		 }
	 }
 }
		 
		 
		 
     refresh(); 
     getch(); 
     endwin();
     return 0; 
 }

*/
