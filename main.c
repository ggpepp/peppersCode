#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "avlTree.h"
#include "log.h"



int main(){	
	initscr();
	int x = 0;
	int y = 0;
	getmaxyx(stdscr,y,x);
	WINDOW * win = newwin(3,x,0,0);
	refresh();
	mvwprintw(win,1,x/2-2,"Loading");
	box(win,0,0);
	wrefresh(win);
	refresh();



		struct database *firstNode = malloc(sizeof(struct database*));
		int lines = 0;
		lines = createDatabase("data.tsv", firstNode);
		if (firstNode->next == NULL) {
			printf("Empty data set\n");
		}
		if (lines < 0)
		{ 
			printf("Data file is not present.\nMake sure that the \"data.tsv\" file is present and restart the program.\n");
			return 1;
		}
		else {
			AVLTREE* tree = createTree();
			DATABASE* currNode = firstNode->next;
			insertNodeByName(tree,currNode);
			for(int i = 0; i < 100; i++)
			{
				currNode = currNode->next;
				insertNodeByName(tree,currNode);
			}
		}
		//Ends initial setup
	mvwprintw(win,1,x/2-2,"Welcome");
	wrefresh(win);
	WINDOW *win2 = newwin(y-3,x,3,0);
	refresh();
	box(win2,0,0);
	mvwprintw(win2,1,x/2-10,"This is the IMDB Database");
	WINDOW *menuWin = newwin(7,x-4,y-10,2);
	box(menuWin,0,0);
	refresh();
	wrefresh(win2);
	wrefresh(menuWin);
	keypad(menuWin, true);

	char choices[2][7] = {"start", "exit"};
	int choice =0;
	int highlight = 0;
	while(1)
	{
		for(int i = 0; i < 2; i++)
		{
			if(i==highlight)
			{
				wattron(menuWin, A_REVERSE);
			}
			mvwprintw(menuWin, 1, 1+i*7, "%s", choices[i]);
			wmove(menuWin,5,x-7);
			wrefresh(menuWin);
			refresh();
			wattroff(menuWin, A_REVERSE);
		}
		choice = wgetch(menuWin);

		switch (choice)
		{
			case KEY_LEFT:
				highlight--;
				if(highlight == -1) highlight = 0;
				break;
		
			case KEY_RIGHT:
				highlight++;
				if(highlight == 2) highlight = 1;
				break;

			default:
				break;
		}
		if(choice == 10)
		break;
		
	}
	if (highlight == 0) 
	{
		char username[50];
		mvwprintw(menuWin, 1,1,"Enter your username:");
		wgetstr(menuWin,username);
		strcat(username, ".log");
		LOG* userLog = readFile(username);
		if(userLog == NULL)
		{
			userLog = createNewLog(username);
		}
		WINDOW* usermenu = newwin(y-8,x-4,5,2);
		box(usermenu,0,0);
		mvwprintw(win2,1,x/2-10,"Movie data for %s", username);
		refresh();
		wrefresh(win2);
		wrefresh(usermenu);
		keypad(usermenu, true);
		while(1)
		{
			int i =0;
			TITLELIST* currNode = userLog->recentAdded->next;
			while(currNode != NULL)
			{
				mvwprintw(usermenu,1+i,1, "%s", currNode->title);
				currNode = currNode->next;
				i++;
			}
			wrefresh(usermenu);
			char choices2[2][10] = {"add", "delete"};
			int choice =0;
			int highlight = 0;
			while(1)
			{
				for(int i = 0; i < 2; i++)
				{
					if(i==highlight)
					{
						wattron(usermenu, A_REVERSE);
					}
					mvwprintw(usermenu, y-20, 1+i*5, "%s", choices2[i]);
					wrefresh(usermenu);
					refresh();
					wattroff(usermenu, A_REVERSE);
				}
				choice = wgetch(usermenu);

				switch (choice)
				{
					case KEY_LEFT:
						highlight--;
						if(highlight == -1) highlight = 0;
						break;
				
					case KEY_RIGHT:
						highlight++;
						if(highlight == 2) highlight = 1;
						break;

					default:
						break;
				}
				if(choice == 10)
				break;
			}
			if(highlight == 0)//Add
			{

				break;
			}
			else
			{
				break;
			}
		}

	}
	else
	{
		endwin();
		return 0;
	}
	
	

	getch();
	endwin();
	return 0;
}