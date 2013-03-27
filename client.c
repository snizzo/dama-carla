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



int main(int argc, char * argv[])
{	
	
	setInterface();
	void allBlack();
	
	struct board b;
	
	setAllBoardEmpty(&b);
	prepareBoard(&b);
	 
	struct moveinfo * move = takeMove(&b);
	printAfterMove(&b);
	
	sleep(5);
	
	unsetInterface();
	
	
//	printf ("%s - %s - %s - %s", move->daC, move->daL, move->aC, move->aL);
		
	
	/*
	
	//evaluating additional parameters
	evaluateParams(argc,argv);
	
	//initializing client network
	struct client_network net;
	
	//creating the user structure that will take record of the user info and current state
	struct clientuser * me = malloc(sizeof(struct clientuser));
	me->logged = 0;
	
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
			case 0: //logout
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
			case 1: //join game
				singleWindowMessage("Waiting for player...");
				char * gameid = joinGame(&net, me);
				singleWindowMessage("Game Found!");
				sleep(4);
				break;
		}
		break;
		
	}
	
	unsetInterface(); //unset ncurses
	
	return 0;
  
}
/*
 * Wait for a game and connect.
 */ /*
char * joinGame(struct client_network * net, struct clientuser * me)
{
	
	while(1){
		fullClientCommand(net, "join","","","",me->loginkey);
		struct netmessage * incoming = readClientMessage(net);
		
		if(areEqual(incoming->msg1, "ready")){
			return incoming->msg2;
		} else {
			sleep(1);
		}
	}
	
}

/*
 * Evaluate additional lauch parameters
 */ /*
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
	}  */
}

//various utils
int even(int n) {
	if ((n % 2)==0) {
		return 1;
	} else {
		return 0;
	}
}

 
 struct moveinfo * takeMove(struct board * b)
{
	FIELD * field[5];
	FORM  * my_form;
	int ch;
	
	/* Initialize the fields */
	field[0] = new_field(1, 1, 3, 52, 0, 0);
	field[1] = new_field(1, 1, 3, 54, 0, 0);
	field[2] = new_field(1, 1, 5, 52, 0, 0);
	field[3] = new_field(1, 1, 5, 54, 0, 0);
	field[4] = NULL;
	
	/* Set field options */
	set_field_back(field[0], A_UNDERLINE); 	/* Print a line for the option 	*/
	field_opts_off(field[0], O_AUTOSKIP);  	/* Don't go to next field when this */
						/* Field is filled up 		*/
	set_field_back(field[1], A_UNDERLINE); 
	field_opts_off(field[1], O_AUTOSKIP);
	
	set_field_back(field[2], A_UNDERLINE); 
	field_opts_off(field[2], O_AUTOSKIP);
	
	set_field_back(field[3], A_UNDERLINE); 
	field_opts_off(field[3], O_AUTOSKIP);

	/* Create the form and post it */
	my_form = new_form(field);
	post_form(my_form);
	refresh();
	
	mvprintw(1, 42, "8"); 
	mvprintw(4, 42, "7"); 
	mvprintw(7, 42, "6"); 
	mvprintw(10, 42, "5"); 
	mvprintw(13, 42, "4"); 
	mvprintw(16, 42, "3"); 
	mvprintw(19, 42, "2"); 
	mvprintw(22, 42, "1"); 
	mvprintw(25, 2, "a"); 
	mvprintw(25, 7, "b"); 
	mvprintw(25, 12, "c"); 
	mvprintw(25, 17, "d"); 
	mvprintw(25, 22, "e"); 
	mvprintw(25, 27, "f"); 
	mvprintw(25, 32, "g"); 
	mvprintw(25, 37, "h"); 

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
	init_pair(4,COLOR_WHITE,COLOR_BLACK);
	attron(COLOR_PAIR(4));
 
	mvprintw(1, 49, "Inserisci la tua prossima mossa");
	mvprintw(3, 49, "da:");
	mvprintw(5, 49, "a:");
	refresh();
	
	int exitCond = 0;
	
	/* Loop through to get user requests */
	while(!exitCond)
	{	
		ch = getch();
		
		switch(ch)
		{	
			case '\n':
				exitCond = 1;
				break;
			
			case KEY_BACKSPACE:
				/* if backspace is hit, a char disappear*/
				form_driver(my_form, REQ_DEL_PREV);
				break;
			
			case KEY_DOWN:
				/* Go to next field */
				form_driver(my_form, REQ_NEXT_FIELD);
				/* Go to the end of the present buffer */
				/* Leaves nicely at the last character */
				form_driver(my_form, REQ_END_LINE);
				break;
			case KEY_UP:
				/* Go to previous field */
				form_driver(my_form, REQ_PREV_FIELD);
				form_driver(my_form, REQ_END_LINE);
				break;
			default:
				/* If this is a normal character, it gets */
				/* Printed				  */	
				form_driver(my_form, ch);
				break;
		}
	}
	
	/* in any case, this small fix is needed in order to get data */
	form_driver(my_form, REQ_PREV_FIELD);
	form_driver(my_form, REQ_END_LINE);
	
	char * daC = field_buffer(field[0],0);
	char * daL = field_buffer(field[1],0);
	char * aC = field_buffer(field[2],0);
	char * aL = field_buffer(field[3],0);
	
	struct moveinfo * data = malloc(sizeof(struct moveinfo));
	
	data->daC = copystring(daC);
	data->daL = copystring(daL);
	data->aC = copystring(aC);
	data->aL = copystring(aL);
	
	int i = 8 - atoi(data->daL);
	int j;
	if (strcmp(data->daC, "a")==0) {
					j = 0;
				} else if (strcmp(data->daC, "b")==0) {
					j = 1;
				} else if (strcmp(data->daC, "c")==0) {
					j = 2;
				} else if (strcmp(data->daC, "d")==0) {
					j = 3;
				} else if (strcmp(data->daC, "e")==0) {
					j = 4;
				} else if (strcmp(data->daC, "f")==0) {
					j = 5;
				} else if (strcmp(data->daC, "g")==0) {
					j = 6;
				} else if (strcmp(data->daC, "h")==0) {
					j = 7;
				}
				
	int k = 8 - atoi(data->aL);
	int l;
	if (strcmp(data->aC, "a")==0) {
					l = 0;
				} else if (strcmp(data->aC, "b")==0) {
					l = 1;
				} else if (strcmp(data->aC, "c")==0) {
					l = 2;
				} else if (strcmp(data->aC, "d")==0) {
					l = 3;
				} else if (strcmp(data->aC, "e")==0) {
					l = 4;
				} else if (strcmp(data->aC, "f")==0) {
					l = 5;
				} else if (strcmp(data->aC, "g")==0) {
					l = 6;
				} else if (strcmp(data->aC, "h")==0) {
					l = 7;
				}
					
	
	/* Un post form and free the memory */
	unpost_form(my_form);
	free_form(my_form);
	free_field(field[0]);
	free_field(field[1]);
	free_field(field[2]);
	free_field(field[3]);
/*
	printf("  ");     //deubg
	printf("%d", i);
	printf("%d", + j);
	printf("%d", + k);
	printf("%d", + l);
*/			
	nextMove( b, i, j, k, l, 1);
	
	
	return data;
}

void printAfterMove(struct board * b) {
	refresh();
	mvprintw(1, 42, "8"); 
	mvprintw(4, 42, "7"); 
	mvprintw(7, 42, "6"); 
	mvprintw(10, 42, "5"); 
	mvprintw(13, 42, "4"); 
	mvprintw(16, 42, "3"); 
	mvprintw(19, 42, "2"); 
	mvprintw(22, 42, "1"); 
	mvprintw(25, 2, "a"); 
	mvprintw(25, 7, "b"); 
	mvprintw(25, 12, "c"); 
	mvprintw(25, 17, "d"); 
	mvprintw(25, 22, "e"); 
	mvprintw(25, 27, "f"); 
	mvprintw(25, 32, "g"); 
	mvprintw(25, 37, "h"); 

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
}
