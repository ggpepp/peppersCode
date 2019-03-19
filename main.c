#include <ncurses.h>
#include <stdlib.h>
#include "database.h"
 
int main(void){	

	struct database *firstNode = malloc(sizeof(struct database*));
	int lines = 0;
	lines = createDatabase("data.tsv", firstNode);
	if (lines < 0) 
	{ 
		puts("Data file is not present.\nMake sure that the \"data.tsv\" file is present and restart the program.\n");
		return 1;
	}
	else { 
		printf("%d\n", lines);
		struct database* currNode = malloc(sizeof(struct database*));

		for(int i = 0; i < 1; i++)
		{
			//printDatabase(currNode);
			//currNode = currNode->next;
		}
	}
	/*
	initscr();			Start curses mode 
	int x = 0;
	int y = 0;
	getmaxyx(stdscr,y,x);
	WINDOW * win = newwin(y,x,0,0);
	refresh();
	box(win,0,0);
	wrefresh(win);
	getch();
	getch();
	getch();
	endwin();			 End curses mode */
	return 0;
}