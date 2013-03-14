#include <stdio.h>
#include <stdlib.h>

//specific lib inclusion
#include "network_data.h"
#include "network.h"
#include "filesystem.h"
#include "auth.h"
#include "list.h"

int main()
{	
	
	//initializing server network
	struct server_network net;
	openServerNetwork(&net);
	
	struct llist * users = createList();
	
	
	while(net.incoming)
	{
		struct netmessage * message = readServerMessage(&net);
		
		// COMMAND: PING
		if (areEqual("ping", message->msg1)) {
			singleCommand(&net, "pong");
		
		// COMMAND: AUTHPING
		} else if (areEqual("authping", message->msg1)) {
			char * loginkey = message->msg5;
			struct user * logged = getUserFromKey(users, loginkey);
			
			if(logged!=NULL){
				fullCommand(&net, "authpong", logged->username, "", "", "");
			} else {
				fullCommand(&net, "unauthorized", "", "", "", "");
			}
		
		// COMMAND: REGISTER <nickname> <password>
		} else if (areEqual("register", message->msg1)) {
			if(!isPresentRecord("users", message->msg2)){
				saveRecord("users", message->msg2, message->msg3);
				
				singleCommand(&net, "done");
			} else {
				singleCommand(&net, "alreadythere");
			}
		
		
		// COMMAND: LOGIN <nickname> <password>
		} else if (areEqual("login", message->msg1)) {
			if(isPresentRecord("users", message->msg2)){
				char * password = readRecord("users", message->msg2);
				
				if (areEqual(password, message->msg3)){
					//generating temporary login key (30 chars long) to be sent to the client
					char * key = generateLoginId(); //WARNING: key DOESN'T GET FREED! CURRENTLY MEMLEAKING! 
					
					
					char * nick = copystring(message->msg2);
					struct user * u = createUser(0,0,"",key,nick,password);
					appendUserNode(users, u);
					
					printf("-----LOGGED------\n");
					printf("Username: %s\n", message->msg2);
					printf("Password: %s\n", password);
					printf("Key     : %s\n", key);
					fullCommand(&net, "done", key, "", "", "");
				} else {
				singleCommand(&net, "wrongpassword");
				}
				
				free(password);
			} else {
				singleCommand(&net, "usernotfound");
			}
			
			
		// COMMAND: <unknown>
		} else {
			singleCommand(&net, "commandnotfound");
		}
		
	}
	
	free(users);
	closeServerNetwork(&net);
	
	return EXIT_SUCCESS;
}
