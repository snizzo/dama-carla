#ifndef CLIENT_H
#define CLIENT_H

struct clientuser {
	char * loginkey;
	char * username;
	char * password;
	char * currentgame;
	int logged;
	int wins;
	int losses;
};

struct moveinfo{
	char * da;
	char * a;
};

int even(int n);
void evaluateParams(int argc, char * argv[]);
int setBox(struct board * b);
int even(int n);
struct moveinfo * takeMove();
struct moveinfo * takeMove(struct board * b);

char * joinGame(struct client_network * net, struct clientuser * me);

#endif
