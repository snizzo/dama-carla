#ifndef INTERFACE_H
#define INTERFACE_H
//ncurses lib inclusion
#include <ncurses.h>
#include <form.h>
#include <string.h>
#include <stdlib.h>

#include "auth.h"

void setInterface(void);
struct logininfo * showLoginForm(void);
void unsetInterface(void);
void singleWindowMessage(char * message);
int showMainMenu(void);
void allBlack(void);
int even(int n);
struct moveinfo * takeMove(struct board * b);
void printAfterMove(struct board * b);

#endif
