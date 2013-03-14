/*
 * This file declares a linked list object, used for dynamically
 * growing lists of objects.
 */

#include "list.h"

struct llist * createList()
{
	struct llist * l = malloc(sizeof(struct llist)*1);
	l->first = NULL;
	
	return l;
}

struct lnode * getLastNode(struct llist * l, struct lnode * n)
{
	if (n!=NULL){
		if (n->next!=NULL){
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

void appendUserNode(struct llist * l, struct user * u1)
{
	//create node
	struct lnode * node = malloc(sizeof(struct lnode)*1);
	node->d->u = u1;
	node->next = NULL;
	
	//append node to last node of the list
	struct lnode * last = getLastNode(l, NULL);
	
	if (last==NULL){ //if list is empty
		l->first = node;
	} else {
		last->next = node;
	}
	
}
