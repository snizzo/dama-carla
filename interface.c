#include "interface.h"

void setInterface()
{
	// Initialize curses
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	start_color();
	}

void allBlack() {
	for (int i=0; i<=COLS; i++) {
		for (int j=0; j<=LINES; j++) {
			init_pair(1,COLOR_BLACK,COLOR_BLACK);
			attron(COLOR_PAIR(1));
			mvprintw(i, j, "");
		}
	}
}

struct logininfo * showLoginForm()
{
	FIELD * field[3];
	FORM  * my_form;
	int ch;
	
	/* Initialize the fields */
	field[0] = new_field(1, 25, 4, 20, 0, 0);
	field[1] = new_field(1, 25, 6, 20, 0, 0);
	field[2] = NULL;
	
	/* Set field options */
	set_field_back(field[0], A_UNDERLINE); 	/* Print a line for the option 	*/
	field_opts_off(field[0], O_AUTOSKIP);  	/* Don't go to next field when this */
						/* Field is filled up 		*/
	set_field_back(field[1], A_UNDERLINE); 
	field_opts_off(field[1], O_AUTOSKIP);

	/* Create the form and post it */
	my_form = new_form(field);
	post_form(my_form);
	refresh();
	
	mvprintw(2, 10, "DAMA CARLA v0.1");
	mvprintw(4, 10, "Username:");
	mvprintw(6, 10, "Password:");
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
	
	char * username = field_buffer(field[0],0);
	char * password = field_buffer(field[1],0);
	
	struct logininfo * data = malloc(sizeof(struct logininfo));
	
	data->username = copystring(username);
	data->password = copystring(password);
	
	/* Un post form and free the memory */
	unpost_form(my_form);
	free_form(my_form);
	free_field(field[0]);
	free_field(field[1]);
	
	return data;
}

/*
 * returns:
 * 0: logout
 * 1: join game
 */
int showMainMenu()
{
	clear();
	refresh();
	int ch;
	
	mvprintw(2, 10, "DAMA CARLA v0.1");
	mvprintw(4, 10, "J  : join a game");
	mvprintw(6, 10, "Q  : logout");
	refresh();
	
	/* Loop through to get user requests */
	while(1)
	{	
		ch = getch();
		
		switch(ch)
		{	
			case 'q': //logout
				return 0;
			
			case 'j':      //join a game
				return 1;
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


struct moveinfo * takeMove(struct board * b, int color)
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
	
	switch(color){
		case 1:
			printWhiteBoard(b);
			break;
		case 2:
			printBlackBoard(b);
			break;
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
	
	return data;
}

void printWhiteBoard(struct board * b) {
	init_pair(4,COLOR_WHITE,COLOR_BLACK);
	attron(COLOR_PAIR(4));
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

void printBlackBoard(struct board * b) {
	int vettore[8][8];
	for (int i=0;i<8;i++){
		for (int j=0;j<8;j++){
			vettore[i][j]=b->data[7-i][7-j];
		}
	}
	init_pair(4,COLOR_WHITE,COLOR_BLACK);
	attron(COLOR_PAIR(4));
	mvprintw(1, 42, "1"); 
	mvprintw(4, 42, "2"); 
	mvprintw(7, 42, "3"); 
	mvprintw(10, 42, "4"); 
	mvprintw(13, 42, "5"); 
	mvprintw(16, 42, "6"); 
	mvprintw(19, 42, "7"); 
	mvprintw(22, 42, "8"); 
	mvprintw(25, 2, "h"); 
	mvprintw(25, 7, "g"); 
	mvprintw(25, 12, "f"); 
	mvprintw(25, 17, "e"); 
	mvprintw(25, 22, "d"); 
	mvprintw(25, 27, "c"); 
	mvprintw(25, 32, "b"); 
	mvprintw(25, 37, "a"); 

	init_pair(1,COLOR_WHITE,COLOR_WHITE);
	init_pair(2,COLOR_WHITE,COLOR_BLACK);
	init_pair(3,COLOR_MAGENTA,COLOR_BLACK);
	for (int a=0; a<8; a++) {
		for (int c=0; c<8; c++) {
		 int k=a*3;
		 int l=c*5;
		 if (vettore[a][c]==1) {
			 attron(COLOR_PAIR(2));
			 for (int i=k; i<k+3; i++) {
				 for (int j=l; j<l+5; j++) {
					 mvprintw(i, j, " ");
				 }
			 }
			 mvprintw(k+1, l+2, "O");
		 } else if (vettore[a][c]==2) {
			 attron(COLOR_PAIR(2));
			 for (int i=k; i<k+3; i++) {
				 for (int j=l; j<l+5; j++) {
					 mvprintw(i, j, " ");
				 }
			 }
			 mvprintw(k+1, l+2, "@");
		 } else if (vettore[a][c]==3) {
			 attron(COLOR_PAIR(3));
			 for (int i=k; i<k+3; i++) {
				 for (int j=l; j<l+5; j++) {
					 mvprintw(i, j, " ");
				 }
			 }
			 mvprintw(k+1, l+2, "O");
		 } else if (vettore[a][c]==4) {
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

void singleWindowMessage(char * message)
{
	clear();
	refresh();
	mvprintw(5, 10, message);
	refresh();
}


void unsetInterface()
{
	endwin();
}
