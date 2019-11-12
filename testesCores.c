#include <ncurses.h>

int main ()
{
	initscr();
	start_color ();
	init_color(COLOR_RED,408,0,408);
	init_pair(1,COLOR_RED,COLOR_BLACK);
	attron(COLOR_PAIR(1));

	clear();
	mvprintw(10,10,"meu terminal aguenta %d cores",COLORS);
	refresh();
	char k = getch ();
	attron(COLOR_PAIR(1));
	init_color(COLOR_RED,700,0,0);		
	endwin();
	return 1;
}
