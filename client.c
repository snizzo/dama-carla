#include <stdio.h>
#include <stdlib.h>


//specific lib inclusion
#include "client.h"



int main(int argc, char * argv[])
{	
	
	//prepare ncurses interface
	setInterface();
	
	//set everything to use black/white, in case terminal colors are different
	allBlack();
	
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
				sleep(1);
				
				int result = playGame(&net, gameid, me);
				if(result){
					singleWindowMessage("Game Won!");
				} else {
					singleWindowMessage("Game Lost!");
				}
				
				break;
		}
		break;
		
	}
	
	unsetInterface(); //unset ncurses
	
	return 0;
  
}

int playGame(struct client_network * net, char * gameid, struct clientuser * me)
{
	int color = 0;
	
	fullClientCommand(net, "opponent","","",gameid,me->loginkey);
	struct netmessage * incoming = readClientMessage(net);
	if(areEqual(incoming->msg1, "thinking")){
		color = 2;
	} else if(areEqual(incoming->msg1, "yourmove")){
		color = 1;
	}
	
	//preparing board
	struct board b;
	setAllBoardEmpty(&b);
	prepareBoard(&b);
	
	while(1){
		//retrieving server game status
		fullClientCommand(net, "opponent","","",gameid,me->loginkey);
		incoming = readClientMessage(net);
		
		//l'avversario sta pensando
		if(areEqual(incoming->msg1, "thinking")){
			sleep(2);
			continue;
			
		//tocca a te, fai la mossa
		} else if (areEqual(incoming->msg1, "yourmove")) {
			struct moveinfo * move = takeMove(&b);
			
			while(nextMove( &b, move, color)==-1){
				singleWindowMessage("Mossa illegale!");
				sleep(1);
			}
			
			clear();
			refresh();
			printAfterMove(&b);
			
			free(move->daC);
			free(move->aC);
			free(move->daL);
			free(move->aL);
			free(move);
		
		//partita vinta
		} else if (areEqual(incoming->msg1, "gamewon")) {
			return 1;
		
		//partita persa
		} else if (areEqual(incoming->msg1, "gamelost")) {
			return 0;
		}
		
	}
}

/*
 * Wait for a game and connect.
 */
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
