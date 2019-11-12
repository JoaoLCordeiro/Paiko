/*************************************************************************/
/* 		Paiko em C ^-^ by João Lucas Cordeiro  			 */
/*************************************************************************/

#include <stdlib.h>
#include <ncurses.h>
#include <string.h>

#define EMPTY 0
#define UNAVAILABLE -1
#define BLACKSQR -2

#define WAIR   4	/*1 */	
#define WBOW   8	/*2 */	
#define WEARTH 12	/*3 */	
#define WFIRE  16	/*4 */	
#define WLOTUS 20	/*5 */	
#define WSAI   24	/*6 */	
#define WSWORD 28	/*7 */	
#define WWATER 32	/*8 */	
#define BAIR   36	/*9 */	
#define BBOW   40	/*10*/	
#define BEARTH 44	/*11*/	
#define BFIRE  48	/*12*/	
#define BLOTUS 52	/*13*/	
#define BSAI   56	/*14*/	
#define BSWORD 60	/*15*/	
#define BWATER 64	/*16*/

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
			{
				if ( ((i==5)&&(j==5)) || ((i==6)&&(j==7)) || ((i==7)&&(j==6)) || ((i==8)&&(j==8)) )
					board->m[i][j]->piece = BLACKSQR;
				else
					board->m[i][j]->piece = EMPTY;
			}
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
			else if (board->m[i][j]->piece == -2)
			{
				wattron  (wboard,COLOR_PAIR(18));
				mvwprintw (wboard, 1+i*3, 1+j*5, "+---+");
                                mvwprintw (wboard, 2+i*3, 1+j*5, "|   |");
                                mvwprintw (wboard, 3+i*3, 1+j*5, "+---+");
				wattroff (wboard,COLOR_PAIR(18));
			}
			if ((i>=7)&&(j<7))             	
                		wattroff (wboard,COLOR_PAIR(1));
                	else if ((i<7)&&(j>=7))
                		wattroff (wboard,COLOR_PAIR(2));
                	else
                		wattroff (wboard,COLOR_PAIR(3));
		}
	}
	mvwprintw (wboard, 1, 2, "What do you want to do?");
	mvwprintw (wboard, 2, 2, "b - buy tiles");
	mvwprintw (wboard, 3, 2, "m - move tiles");
	mvwprintw (wboard, 4, 2, "d - deploy tiles");
	box (wboard,0,0);
	wrefresh(wboard);
}

void initializes_v(int *tv_white,int *tv_black,int n)	/*puts "zero" in all the tiles vectors*/
{
	int i;
	for (i=0 ;i<8 ; i++)
	{
		tv_white[i] = n;
		tv_black[i] = n;
	}
}

void initializes_p (char **tiles)
{
	strcpy (tiles[0],"Air  ");
	strcpy (tiles[1],"Bow  ");
	strcpy (tiles[2],"Earth");
	strcpy (tiles[3],"Fire ");
	strcpy (tiles[4],"Lotus");
	strcpy (tiles[5],"Sai  ");
	strcpy (tiles[6],"Sword");
	strcpy (tiles[7],"Water");
}

void print_vector (WINDOW *win,int *white,int *black,char **tiles)
{
	int i;
	for (i=0 ; i<8 ; i++)
	{
		wattron(win,COLOR_PAIR(10+i));
		mvwprintw (win, 5+i  , 5  , tiles[i]);
		mvwprintw (win, 20+i , 5  , tiles[i]);
		mvwprintw (win, 5+i  , 10 , " = %d",white[i]);
	        mvwprintw (win, 20+i , 10 , " = %d",black[i]);
		wattroff(win,COLOR_PAIR(10+i));
	}
	box(win,0,0);
	wrefresh(win);							
}

void buy_tiles (int *hand,int *reserve)
{
	int i = 0;
	int k;
	while (i<3)
	{
		scanw("%d",&k);
		if ((k >= 0)&&(k < 8))
		{
			if (reserve[k] != 0)
			{
				reserve[k]--;
				hand[k]++;
				i++;
			}
		}
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

	init_color(10,1000,600 ,0   );			/*Orange*/
	init_color(11,400 ,400 ,0   );			/*Brown*/
	init_color(12,400 ,0   ,400 );			/*Purple*/
	init_color(13,600 ,600 ,600 );			/*Grey*/
	init_color(14,200 ,200 ,200 );
	init_pair(1,COLOR_GREEN   ,COLOR_BLACK);
	init_pair(2,10            ,COLOR_BLACK);
	init_pair(3,13            ,COLOR_BLACK);

	init_pair(10,COLOR_CYAN	  ,COLOR_BLACK);	/*Air color*/
	init_pair(11,11		  ,COLOR_BLACK);	/*Bow color*/
	init_pair(12,COLOR_GREEN  ,COLOR_BLACK);	/*Earth color*/
	init_pair(13,COLOR_RED	  ,COLOR_BLACK);	/*Fire color*/
	init_pair(14,COLOR_MAGENTA,COLOR_BLACK);	/*Lotus color*/
	init_pair(15,12		  ,COLOR_BLACK);	/*Sai color*/
	init_pair(16,13		  ,COLOR_BLACK);	/*Sword color*/
	init_pair(17,COLOR_BLUE   ,COLOR_BLACK);	/*Water color*/
	init_pair(18,14		  ,COLOR_BLACK);	/*Black square color*/

	t_board board;
	int hv_white[8];
	int hv_black[8];
	int rv_white[8];
	int rv_black[8];
	char **tiles;
	int finish = 0;
	int player = 0;		/*zero = white, one = black*/
	tiles = (char **) malloc (8*sizeof(char *));
	int i;
        for (i=0 ; i<8 ; i++)
        	tiles[i] =  (char *) malloc (6*sizeof(char));

	initializes_p	  (tiles);
	initializes_v	  (hv_white,hv_black,0);
	initializes_v	  (rv_white,rv_black,3);
	initializes_board (&board);

	while (! finish)
	{
		print_board 	  (wboard,&board);
		print_vector	  (whand   ,hv_white,hv_black,tiles);
		print_vector	  (wreserve,rv_white,rv_black,tiles);
		char k = getch();
		if (k == 'b') 	/*makes buy tiles*/
		{
			mvwprintw(wboard, 40 , 2 , "Escreva o numero da");
			mvwprintw(wboard, 41 , 2 , "peça e aperte ENTER");
			wrefresh(wboard);
			if (! player)
				buy_tiles (hv_white,rv_white);
			else
				buy_tiles (hv_black,rv_black);
		}
		else if (k == 'm')
		{
			/*makes maves tiles*/
		}
		else if (k == 'd')
		{
			/*makes deploy tiles*/
		}
		else if (k == 'q')
			finish = 1;
		player = (player+1)%2;
	}	
	endwin();
	return 1;
}
