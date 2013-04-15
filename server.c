#include <stdio.h>
#include <stdlib.h>

//specific lib inclusion
#include "network_data.h"
#include "network.h"
#include "filesystem.h"
#include "auth.h"
#include "list.h"
#include "logic.h"
#include "structs.h"

void evaluateParams(int argc, char * argv[]);
char * fromCharToPChar(char p);

int main(int argc, char * argv[])
{	
	
	evaluateParams(argc, argv);
	
	//initializing server network
	struct server_network net;
	openServerNetwork(&net);
	
	struct llist * users = createList();
	struct llist * games = createList();
	
	//player waiting for other player to connect
	struct user * waiting = NULL;
	
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
		
		// COMMAND: LOGOUT
		} else if (areEqual("logout", message->msg1)) {
			char * loginkey = message->msg5;
			struct user * logged = getUserFromKey(users, loginkey);
			
			if(logged!=NULL){
				deleteUserNode(users,loginkey);
				fullCommand(&net, "done", "", "", "", "");
			} else {
				fullCommand(&net, "unauthorized", "", "", "", "");
			}
		
		/*
		 * This one is useful to retrieve game information
		 */
		// COMMAND: OPPONENT
		} else if (areEqual("opponent", message->msg1)) {
			char * loginkey = message->msg5;
			struct user * logged = getUserFromKey(users, loginkey);
			
			
			if(logged!=NULL){
				struct game * found = getGameFromPlayer(games, logged->key);
				if(found!=NULL){
					if(found->status==1 && areEqual(found->white, logged->key)){
						if(found->lastmove!=NULL){						
							fullCommand(&net, "yourmove", found->lastmove, "", "", "");
						} else {
							fullCommand(&net, "yourmove", "", "", "", "");
						}
					} else if(found->status==1 && areEqual(found->black, logged->key)){
						fullCommand(&net, "thinking", "", "", "", "");
					} else if(found->status==2 && areEqual(found->white, logged->key)){
						fullCommand(&net, "thinking", "", "", "", "");
					} else if(found->status==2 && areEqual(found->black, logged->key)){
						if(found->lastmove!=NULL){
							fullCommand(&net, "yourmove", found->lastmove, "", "", "");
						} else {
							fullCommand(&net, "yourmove", "", "", "", "");
						}
					} else if(found->status==3 && areEqual(found->white, logged->key)){
						fullCommand(&net, "gamewon", "", "", "", "");
					} else if(found->status==4 && areEqual(found->black, logged->key)){
						fullCommand(&net, "gamewon", "", "", "", "");
					} else if(found->status==3 && areEqual(found->black, logged->key)){
						fullCommand(&net, "gamelost", "", "", "", "");
					} else if(found->status==4 && areEqual(found->white, logged->key)){
						fullCommand(&net, "gamelost", "", "", "", "");
					}
					continue;
				} else {
					fullCommand(&net, "gamenotfound", "", "", "", "");
				}
			} else {
				fullCommand(&net, "unauthorized", "", "", "", "");
			}
		
		// COMMAND: MOVE
		} else if (areEqual("move", message->msg1)) {
			char * loginkey = message->msg5;
			struct user * logged = getUserFromKey(users, loginkey);
			
			char * move = message->msg2;
			
			
			if(logged!=NULL){
				struct game * found = getGameFromPlayer(games, logged->key);
				if(found!=NULL){
					
					printf("performing move for player\n" );
					printf("status: %i\n", found->status);
					printf("move: %s\n", move);
					free(found->lastmove);
					
					struct moveinfo * trymove = malloc(sizeof(struct moveinfo));
				
					trymove->daC = fromCharToPChar(message->msg2[0]);
					trymove->daL = fromCharToPChar(message->msg2[1]);
					trymove->aC = fromCharToPChar(message->msg2[2]);
					trymove->aL = fromCharToPChar(message->msg2[3]);
					
					int color = 1;
					
					if(areEqual(logged->key, found->black)){
						color = 2;
					}
					
					if(nextMove(found->currentboard, trymove, color)==1){
						found->lastmove = copystring(move);
						
						if(found->status==1){
							found->status = 2;
						} else if(found->status==2){
							found->status = 1;
						}
						
						fullCommand(&net, "accepted", "", "", "", "");
					} else {
						fullCommand(&net, "rejected", "", "", "", "");
					}
					
					free(trymove->aL);
					free(trymove->aC);
					free(trymove->daL);
					free(trymove->daC);
					free(trymove);
					
				} else {
					fullCommand(&net, "gamenotfound", "", "", "", "");
				}
			} else {
				fullCommand(&net, "unauthorized", "", "", "", "");
			}
		
		// COMMAND: JOIN
		} else if (areEqual("join", message->msg1)) {
			char * loginkey = message->msg5;
			struct user * logged = getUserFromKey(users, loginkey);
			
			
			if(logged!=NULL){
				struct game * found = getGameFromPlayer(games, logged->key);
				if(found!=NULL){
					fullCommand(&net, "ready", found->key, "", "", "");
					continue;
				}
				
				if(waiting==NULL){
					waiting = logged;
					fullCommand(&net, "wait", "", "", "", "");
				} else {
					if(waiting!=logged){
						//spawn a new game
						char * gameid = generateLoginId();
						struct game * g = createGame(gameid, logged->key, waiting->key);
						
						appendGameNode(games, g);
						
						waiting = NULL;
						
						fullCommand(&net, "ready", gameid, "", "", "");
					} else {
						fullCommand(&net, "wait", "", "", "", "");
					}
				}
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
					char * key = generateLoginId();
					
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

/*
 * Convert from char to char *
 */
char * fromCharToPChar(char p)
{
	char * s = malloc(2);
	s[0] = p;
	s[1] = 0;
	
	return s;
}

/*
 * Evaluate additional lauch parameters
 */
void evaluateParams(int argc, char * argv[])
{
	if ((argc>1) && (areEqual("--help", argv[1]))){
		printf("Dama Carla - Online Dama Server\n");
		printf("Port   : 2343\n");
		printf("Author : Claudio Desideri <happy.snizzo@gmail.com>\n");
		printf("Website: http://dama-carla.googlecode.com\n");
		exit(0);
	}
}
