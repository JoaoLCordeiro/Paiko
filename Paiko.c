/*************************************************************************/
/* 		Paiko em C ^-^ by João Lucas Cordeiro  			 */
/*************************************************************************/

#include <stdlib.h>
#include <ncurses.h>

#define EMPTY 0
#define UNAVAILABLE -1

#define AIR   1
#define BOW   2
#define EARTH 3
#define FIRE  4
#define LOTUS 5
#define SAI   6
#define SWORD 7
#define WATER 8

typedef struct t_square
{
	int th_white;
	int th_black;
	int piece;
	int cv_white;
	int cv_black;
} t_square;

typedef struct t_board
{
	t_square *m[14][14];
} t_board;			

void initializes_board (t_board *board)			/*initializes the squares of the board*/
{
	int i,j;
	for (i=0 ; i<14 ; i++)
	{
		for (j=0 ; j<14 ; j++)
		{
			board->m[i][j] = (t_square *) malloc (sizeof(t_square));
			if (((j+i >= 6)&&(j+i <= 20)) /*cuts the upper-left and lower-right corner*/ && ((j-i <= 7)&&(j-i >= -7))) /*cuts the upper-right and lower-left corner*/
				board->m[i][j]->piece = EMPTY;
			else
				board->m[i][j]->piece = UNAVAILABLE;
			board->m[i][j]->th_white      = 0;
			board->m[i][j]->th_black      = 0;
			board->m[i][j]->cv_white      = 0;
			board->m[i][j]->cv_black      = 0;
		}
	}
}

void print_board (WINDOW *wboard,t_board *board)	/*prints the board*/
{
	int i,j;
	wclear(wboard);
	for (i=0 ; i<14 ; i++)
	{
		for (j=0 ; j<14 ; j++)
		{
			if ((i>=7)&&(j<7))
				wattron (wboard,COLOR_PAIR(1));
			else if ((i<7)&&(j>=7))
				wattron (wboard,COLOR_PAIR(2));
			else
				wattron (wboard,COLOR_PAIR(3));
			if (board->m[i][j]->piece == 0)
			{
				mvwprintw (wboard, 1+i*3, 1+j*5, "+---+");
				mvwprintw (wboard, 2+i*3, 1+j*5, "|   |");
				mvwprintw (wboard, 3+i*3, 1+j*5, "+---+");
			}
			if ((i>=7)&&(j<7))             	
                		wattroff (wboard,COLOR_PAIR(1));
                	else if ((i<7)&&(j>=7))
                		wattroff (wboard,COLOR_PAIR(2));
                	else
                		wattroff (wboard,COLOR_PAIR(3));
		}
	}
	box (wboard,0,0);
	wrefresh(wboard);
}

void initializes_pv(int *pv_white,int *pv_black)	/*puts "zero" in all the piece vectors*/
{
	int i;
	for (i=0 ;i<8 ; i++)
	{
		pv_white[i] = 0;
		pv_black[i] = 0;
	}
}

int main ()
{
	initscr();
	WINDOW *wboard    = newwin (44,72,0,0);
	WINDOW *whand     = newwin (44,20,0,72);
	WINDOW *wreserve  = newwin (44,20,0,92);
	refresh();
	noecho();
	curs_set(FALSE);

	start_color();
	init_pair(1,COLOR_GREEN ,COLOR_BLACK);
	init_pair(2,COLOR_YELLOW  ,COLOR_BLACK);
	init_pair(3,COLOR_CYAN,COLOR_BLACK);

	t_board board;
	int pv_white[8];
	int pv_black[8];

	initializes_pv	  (pv_white,pv_black);
	initializes_board (&board);
	print_board 	  (wboard,&board);
	box (whand,0,0);
	box (wreserve,0,0);
	wrefresh(whand);
	wrefresh(wreserve); 
	char k = getch();
	endwin();
	return 1;
}
