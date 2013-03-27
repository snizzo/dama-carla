/*
 * This file declares a linked list object, used for dynamically
 * growing lists of objects.
 */

#include "list.h"
#include "network.h"

struct llist * createList()
{
	struct llist * l = malloc(sizeof(struct llist)*1);
	l->first = NULL;
	
	return l;
}

struct lnode * getLastNode(struct llist * l, struct lnode * n)
{
	if (n!=NULL){
		if (n->next==NULL){
			return n; //this is the last node
		} else {
			return getLastNode(l, n->next); //return last of the list
		}
	} else {
		if (l->first!=NULL){
			return getLastNode(l, l->first); //return last of the list
		} else {
			return NULL; //list is empty
		}
	}
	
}

void deleteUserNode(struct llist * l, char * key)
{
	deleteUserNodeEngine(key, l->first, NULL, l); //key, current, previous, linked list
}

void deleteUserNodeEngine(char * key, struct lnode * n, struct lnode * previous, struct llist * list)
{
	if(areEqual(n->d.u->key, key)){ // if this is the key to be deleted, delete it
	
		if(previous==NULL){ // this node is the first of the list
			
			if(n->next==NULL){ 		//there's no next node
				list->first = NULL; //first node of linked list does not exist
				free(n->d.u); //free user structure
				free(n); 		//free entire node 
			} else {
				list->first = n->next; //first node of linked list does not exist
				free(n->d.u); //free user structure
				free(n); 		//free entire node
				//there is next node. This next node will become the new first node
			}
			
		} else {
			
			if(n->next==NULL){
				//this node is alone. Just free it and remove reference.
				previous->next = NULL;
				free(n->d.u); //free user structure
				free(n); 		//free entire node
			} else {
				previous->next = n->next;
				free(n->d.u); //free user structure
				free(n); 		//free entire node
			}
			
		}
		
	} else { // if this is not the right node, go ahead
	
		if (n->next!=NULL) {
			deleteUserNodeEngine(key, n->next, n, list);
		}
		
	}

}

struct user * getUserFromKey(struct llist * l, char * key)
{
	if (l->first==NULL){
		return NULL;
	} else {
		return getUserFromKeyEngine(key, l->first);
	}
}

struct user * getUserFromKeyEngine(char * key, struct lnode * n)
{
	if (n->d.u!=NULL){
		//perform search
		if(areEqual(n->d.u->key,key)){
			return n->d.u; //this is the right node
		} else {
			if (n->next!=NULL){
				return getUserFromKeyEngine(key, n->next); //search in the next
			} else {
				return NULL; //not found here
			}
		}
	} else {
		return NULL;
		//empty node: critical errors!!
		//FIXME: maybe automatic whiping...
	}

}

void appendUserNode(struct llist * l, struct user * u1)
{
	//create node
	struct lnode * node = malloc(sizeof(struct lnode)*1);
	node->d.u = u1;
	node->next = NULL;
	
	//append node to last node of the list
	struct lnode * last = getLastNode(l, NULL);
	
	if (last==NULL){ //if list is empty
		l->first = node;
	} else {
		last->next = node;
	}
}
//--------------------------------------GAME LIST

void appendGameNode(struct llist * l, struct game * g1)
{
	//create node
	struct lnode * node = malloc(sizeof(struct lnode)*1);
	node->d.g = g1;
	node->next = NULL;
	
	//append node to last node of the list
	struct lnode * last = getLastNode(l, NULL);
	
	if (last==NULL){ //if list is empty
		l->first = node;
	} else {
		last->next = node;
	}
}

struct game * getGameFromPlayer(struct llist * l, char * key)
{
	if (l->first==NULL){
		return NULL;
	} else {
		return getGameFromPlayerEngine(key, l->first);
	}
}


struct game * getGameFromPlayerEngine(char * key, struct lnode * n)
{
	if (n->d.g!=NULL){
		//perform search
		if(areEqual(n->d.g->white,key) || areEqual(n->d.g->black,key)){
			return n->d.g; //this is the right node
		} else {
			if (n->next!=NULL){
				return getGameFromPlayerEngine(key, n->next); //search in the next
			} else {
				return NULL; //not found here
			}
		}
	} else {
		return NULL;
		//empty node: critical errors!!
		//FIXME: maybe automatic whiping...
	}

}

struct game * getGameFromKey(struct llist * l, char * key)
{
	if (l->first==NULL){
		return NULL;
	} else {
		return getGameFromKeyEngine(key, l->first);
	}
}

struct game * getGameFromKeyEngine(char * key, struct lnode * n)
{
	if (n->d.g!=NULL){
		//perform search
		if(areEqual(n->d.g->key,key)){
			return n->d.g; //this is the right node
		} else {
			if (n->next!=NULL){
				return getGameFromKeyEngine(key, n->next); //search in the next
			} else {
				return NULL; //not found here
			}
		}
	} else {
		return NULL;
		//empty node: critical errors!!
		//FIXME: maybe automatic whiping...
	}

}

void deleteGameNode(struct llist * l, char * key)
{
	deleteGameNodeEngine(key, l->first, NULL, l); //key, current, previous, linked list
}

void deleteGameNodeEngine(char * key, struct lnode * n, struct lnode * previous, struct llist * list)
{
	if(areEqual(n->d.g->key, key)){ // if this is the key to be deleted, delete it
	
		if(previous==NULL){ // this node is the first of the list
			
			if(n->next==NULL){ 		//there's no next node
				list->first = NULL; //first node of linked list does not exist
				free(n->d.g); //free user structure
				free(n); 		//free entire node 
			} else {
				list->first = n->next; //first node of linked list does not exist
				free(n->d.g); //free user structure
				free(n); 		//free entire node
				//there is next node. This next node will become the new first node
			}
			
		} else {
			
			if(n->next==NULL){
				//this node is alone. Just free it and remove reference.
				previous->next = NULL;
				free(n->d.g); //free user structure
				free(n); 		//free entire node
			} else {
				previous->next = n->next;
				free(n->d.g); //free user structure
				free(n); 		//free entire node
			}
			
		}
		
	} else { // if this is not the right node, go ahead
	
		if (n->next!=NULL) {
			deleteGameNodeEngine(key, n->next, n, list);
		}
		
	}

}
