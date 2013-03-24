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

//various utils
int even(int n) {
	if ((n % 2)==0) {
		return 1;
	} else {
		return 0;
	}
}

