#include "interface.h"

void setInterface()
{
	// Initialize curses
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
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
	
	return data; //currently returning 1, maybe to refactor in future
}

void unsetInterface()
{
	endwin();
}
