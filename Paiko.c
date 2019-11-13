/*************************************************************************/
/* 		        Paiko in C ^-^ by João Lucas Cordeiro         			 */
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

#define spriteAIR01 "+---+"
#define spriteAIR02 "| A |"
#define spriteAIR03 "+---+"

#define spriteBOW11 "+-^-+"
#define spriteBOW12 "| B |"
#define spriteBOW13 "+---+"
#define spriteBOW21 "+---+"
#define spriteBOW22 "< B |"
#define spriteBOW23 "+---+"
#define spriteBOW31 "+---+"
#define spriteBOW32 "| B >"
#define spriteBOW33 "+---+"
#define spriteBOW41 "+---+"
#define spriteBOW42 "| B |"
#define spriteBOW43 "+-V-+"

#define spriteEAR01 "+---+"
#define spriteEAR02 "| E |"
#define spriteEAR03 "+---+"

#define spriteFIR11 "+-^-+"
#define spriteFIR12 "| F |"
#define spriteFIR13 "+---+"
#define spriteFIR21 "+---+"
#define spriteFIR22 "< F |"
#define spriteFIR23 "+---+"
#define spriteFIR31 "+---+"
#define spriteFIR32 "| F >"
#define spriteFIR33 "+---+"
#define spriteFIR41 "+---+"
#define spriteFIR42 "| F |"
#define spriteFIR43 "+-V-+"

#define spriteLOT01 "+---+"
#define spriteLOT02 "| L |"
#define spriteLOT03 "+---+"

#define spriteSAI11 "+-^-+"
#define spriteSAI12 "| I |"
#define spriteSAI13 "+---+"
#define spriteSAI21 "+---+"
#define spriteSAI22 "< I |"
#define spriteSAI23 "+---+"
#define spriteSAI31 "+---+"
#define spriteSAI32 "| I >"
#define spriteSAI33 "+---+"
#define spriteSAI41 "+---+"
#define spriteSAI42 "| I |"
#define spriteSAI43 "+-V-+"

#define spriteSWO01 "+---+"
#define spriteSWO02 "| S |"
#define spriteSWO03 "+---+"

#define spriteWAT01 "+---+"
#define spriteWAT02 "| W |"
#define spriteWAT03 "+---+"


typedef struct t_square
{
    int th_white;
    int th_black;
    int tile;
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
                    board->m[i][j]->tile = BLACKSQR;
                else
                    board->m[i][j]->tile = EMPTY;
            }
            else
                board->m[i][j]->tile = UNAVAILABLE;
            board->m[i][j]->th_white      = 0;
            board->m[i][j]->th_black      = 0;
            board->m[i][j]->cv_white      = 0;
            board->m[i][j]->cv_black      = 0;
        }
    }
}

void print_tile (WINDOW *wboard, int i,int j, int tile)
{
    int tileT;  /*have the type of tile*/
    if ((tile >= 4)&&(tile < 36))
        tileT = tile / 4;
    else
        tileT = (tile - 32)/4;
    if (tileT == 1) /*prints air*/
    {
        mvwprintw (wboard, 1+i*3, 1+j*5, spriteAIR01);
        mvwprintw (wboard, 2+i*3, 1+j*5, spriteAIR02);
        mvwprintw (wboard, 3+i*3, 1+j*5, spriteAIR03);
    }
    else if (tileT == 2) /*prints bow*/
    {
        if (tile % 4 == 0)
        {
            mvwprintw (wboard, 1+i*3, 1+j*5, spriteBOW11);
            mvwprintw (wboard, 2+i*3, 1+j*5, spriteBOW12);
            mvwprintw (wboard, 3+i*3, 1+j*5, spriteBOW13);
        }
        else if (tile % 4 == 1)
        {
            mvwprintw (wboard, 1+i*3, 1+j*5, spriteBOW21);
            mvwprintw (wboard, 2+i*3, 1+j*5, spriteBOW22);
            mvwprintw (wboard, 3+i*3, 1+j*5, spriteBOW23);
        }
        else if (tile % 4 == 2)
        {
            mvwprintw (wboard, 1+i*3, 1+j*5, spriteBOW31);
            mvwprintw (wboard, 2+i*3, 1+j*5, spriteBOW32);
            mvwprintw (wboard, 3+i*3, 1+j*5, spriteBOW33);
        }
        else if (tile % 4 == 3)
        {
            mvwprintw (wboard, 1+i*3, 1+j*5, spriteBOW41);
            mvwprintw (wboard, 2+i*3, 1+j*5, spriteBOW42);
            mvwprintw (wboard, 3+i*3, 1+j*5, spriteBOW43);
        }                                                       
    }
    else if (tileT == 3) /*prints earth*/
    {
        mvwprintw (wboard, 1+i*3, 1+j*5, spriteEAR01);
        mvwprintw (wboard, 2+i*3, 1+j*5, spriteEAR02);
        mvwprintw (wboard, 3+i*3, 1+j*5, spriteEAR03);
    }
    else if (tileT == 4) /*prints fire*/
    { 
        if (tile % 4 == 0)
        {
            mvwprintw (wboard, 1+i*3, 1+j*5, spriteFIR11);
            mvwprintw (wboard, 2+i*3, 1+j*5, spriteFIR12);
            mvwprintw (wboard, 3+i*3, 1+j*5, spriteFIR13);
        }
        else if (tile % 4 == 1)
        {
            mvwprintw (wboard, 1+i*3, 1+j*5, spriteFIR21);
            mvwprintw (wboard, 2+i*3, 1+j*5, spriteFIR22);
            mvwprintw (wboard, 3+i*3, 1+j*5, spriteFIR23);
        }
        else if (tile % 4 == 2)
        {
            mvwprintw (wboard, 1+i*3, 1+j*5, spriteFIR31);
            mvwprintw (wboard, 2+i*3, 1+j*5, spriteFIR32);
            mvwprintw (wboard, 3+i*3, 1+j*5, spriteFIR33);
        }
        else if (tile % 4 == 3)
        {
            mvwprintw (wboard, 1+i*3, 1+j*5, spriteFIR41);
            mvwprintw (wboard, 2+i*3, 1+j*5, spriteFIR42);
            mvwprintw (wboard, 3+i*3, 1+j*5, spriteFIR43);
        }                                                       
    }
    else if (tileT == 5) /*prints lotus*/
    {
        mvwprintw (wboard, 1+i*3, 1+j*5, spriteLOT01);
        mvwprintw (wboard, 2+i*3, 1+j*5, spriteLOT02);
        mvwprintw (wboard, 3+i*3, 1+j*5, spriteLOT03);
    }
    else if (tileT == 6) /*prints sai*/
    { 
        if (tile % 4 == 0)
        {
            mvwprintw (wboard, 1+i*3, 1+j*5, spriteSAI11);
            mvwprintw (wboard, 2+i*3, 1+j*5, spriteSAI12);
            mvwprintw (wboard, 3+i*3, 1+j*5, spriteSAI13);
        }
        else if (tile % 4 == 1)
        {
            mvwprintw (wboard, 1+i*3, 1+j*5, spriteSAI21);
            mvwprintw (wboard, 2+i*3, 1+j*5, spriteSAI22);
            mvwprintw (wboard, 3+i*3, 1+j*5, spriteSAI23);
        }
        else if (tile % 4 == 2)
        {
            mvwprintw (wboard, 1+i*3, 1+j*5, spriteSAI31);
            mvwprintw (wboard, 2+i*3, 1+j*5, spriteSAI32);
            mvwprintw (wboard, 3+i*3, 1+j*5, spriteSAI33);
        }
        else if (tile % 4 == 3)
        {
            mvwprintw (wboard, 1+i*3, 1+j*5, spriteSAI41);
            mvwprintw (wboard, 2+i*3, 1+j*5, spriteSAI42);
            mvwprintw (wboard, 3+i*3, 1+j*5, spriteSAI43);
        }                                                       
    }
    else if (tileT == 7) /*prints sword*/
    {
        mvwprintw (wboard, 1+i*3, 1+j*5, spriteSWO01);
        mvwprintw (wboard, 2+i*3, 1+j*5, spriteSWO02);
        mvwprintw (wboard, 3+i*3, 1+j*5, spriteSWO03);
    }
    else                 /*prints water*/
    {
        mvwprintw (wboard, 1+i*3, 1+j*5, spriteWAT01);
        mvwprintw (wboard, 2+i*3, 1+j*5, spriteWAT02);
        mvwprintw (wboard, 3+i*3, 1+j*5, spriteWAT03);
    }
}

void print_board (WINDOW *wboard,t_board *board)	/*prints the board*/
{
    int i,j;
    int tile;
    wclear(wboard);
    for (i=0 ; i<14 ; i++)
    {
        for (j=0 ; j<14 ; j++)
        {
            tile = board->m[i][j]->tile;
            if ((i>=7)&&(j<7))
                wattron (wboard,COLOR_PAIR(1));
            else if ((i<7)&&(j>=7))
                wattron (wboard,COLOR_PAIR(2));
            else
                wattron (wboard,COLOR_PAIR(10));
            if (tile == 0)
            {
                mvwprintw (wboard, 1+i*3, 1+j*5, "+---+");
                mvwprintw (wboard, 2+i*3, 1+j*5, "|   |");
                mvwprintw (wboard, 3+i*3, 1+j*5, "+---+");
            }
            else if (tile == -2)
            {
                wattron  (wboard,COLOR_PAIR(18));
                mvwprintw (wboard, 1+i*3, 1+j*5, "+---+");
                mvwprintw (wboard, 2+i*3, 1+j*5, "|   |");
                mvwprintw (wboard, 3+i*3, 1+j*5, "+---+");
                wattroff (wboard,COLOR_PAIR(18));
            }
            else if ((tile >= 4)&&(tile < 36)) /*white*/
            {
                wattron (wboard,COLOR_PAIR(20));
                print_tile (wboard,i,j,tile);
                wattroff (wboard,COLOR_PAIR(20)); 
            }
            else if ((tile >= 36)&&(tile < 68)) /*black*/
            {
                wattron (wboard,COLOR_PAIR(19)); 
                print_tile (wboard,i,j,tile);
                wattroff (wboard,COLOR_PAIR(19));
            }
            if ((i>=7)&&(j<7))             	
                wattroff (wboard,COLOR_PAIR(1));
            else if ((i<7)&&(j>=7))
                wattroff (wboard,COLOR_PAIR(2));
            else
                wattroff (wboard,COLOR_PAIR(10));
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

void initializes_t (char **tiles)
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

int buy_tiles (int *hand,int *reserve)
{
    int t1,t2,t3;
    scanw("%d %d %d",&t1,&t2,&t3);
    if (t1 && t2 && t3)	/*testing if one or more isn't zero*/
    {
        if ( ((t1 > 0)&&(t1 < 9)) && ((t2 > 0)&&(t2 < 9)) && ((t3 > 0)&&(t3 < 9)) )
        {
            reserve[t1-1]--;
            reserve[t2-1]--;
            reserve[t3-1]--;
            hand[t1-1]++;
            hand[t2-1]++;
            hand[t3-1]++;
            return 1;
        }
    }
    return 0;
}

void print_buy_msg (WINDOW *win)
{
    mvwprintw(win, 39 , 2 , "Write the numbers of");         
    mvwprintw(win, 40 , 2 , "the tiles with spaces");
    mvwprintw(win, 41 , 2 , "between them and press ENTER.");
    mvwprintw(win, 42 , 2 , "Write 0 to cancel.");
    wrefresh(win);
}

int verify_tile_dies_black (t_square *square)
{
    if (((square->tile / 4 == BFIRE/4) && (((square->cv_black == 1)&&(square->th_white + 1 >= 2)) || ((square->cv_black == 0)&&(square->th_white >= 1)))) ||	/*if it's a black fire and it dies*/((square->tile >= 36)&&(square->tile < 68)&&(square->tile < BFIRE)&&(square->tile >= BFIRE + 4)  && (((square->cv_black == 1)&&(square->th_white + 1 >= 3)) || ((square->cv_black == 0)&&(square->th_white >= 2))))) /*its other black tile and it dies*/
        return 1;
    else
        return 0; 
}

int verify_tile_dies_white (t_square *square)
{
    if (((square->tile / 4 == WFIRE/4) && (((square->cv_white == 1)&&(square->th_black + 1 >= 2)) || ((square->cv_white == 0)&&(square->th_black >= 1)))) ||	/*if it's a white fire and it dies*/((square->tile >= 4)&&(square->tile < 36)&&(square->tile < WFIRE)&&(square->tile >= WFIRE + 4) && (((square->cv_white == 1)&&(square->th_black + 1 >= 3)) || ((square->cv_white == 0)&&(square->th_black >= 2))))) /*its other white tile and it dies*/
        return 1;
    else
        return 0;
}

int verify_fire (t_board *board,int lin,int col,int dir,int player)
{
    int i,j;
    t_square *square;   /*BLACK TILES VERIFICATION PART*/
    if (! player)
    {
        if (dir == 1)
        {
            for (i=-2 ; i<0 ; i++)
            {
                if (i == -2)
                {
                    for (j=-2 ; j<3 ; j++)
                    {
                        square = board->m[lin+i][col+j];
                        if ( verify_tile_dies_black (square) )
                            return 0;
                    }
                }
                else
                {
                    for (j=-1 ; j<2 ; j++)
                    {
                        square = board->m[lin+i][col+j];
                        if ( verify_tile_dies_black (square) )
                            return 0;
                    }
                }
            }
            return 1;
        }
        else if (dir == 2)
        {
            for (j=-2 ; j<0 ; j++)
            {
                if (j == -2)
                {
                    for (i=-2 ; i<3 ; i++)
                    {
                        square = board->m[lin+i][col+j];
                        if ( verify_tile_dies_black (square) )
                            return 0;
                    }
                }
                else
                {
                    for (i=-1 ; i<2 ; i++)
                    {
                        square = board->m[lin+i][col+j];
                        if ( verify_tile_dies_black (square) )
                            return 0;
                    }
                }
            }
            return 1;
        }
        else if (dir == 3)
        {
            for (j=1 ; j<3 ; j++) 
            {
                if (j == 2)
                {
                    for (i=-2 ; i<3 ; i++)
                    {
                        square = board->m[lin+i][col+j];
                        if ( verify_tile_dies_black (square) )
                            return 0;
                    }
                }
                else
                {
                    for (i=-1 ; i<2 ; i++)
                    {
                        square = board->m[lin+i][col+j];
                        if ( verify_tile_dies_black (square) )
                            return 0;
                    }
                }
            }
            return 1;
        }
        else
        {
            for (i=1 ; i<3 ; i++) 
            {
                if (i == 2)
                {
                    for (j=-2 ; j<3 ; j++)
                    {
                        square = board->m[lin+i][col+j];
                        if ( verify_tile_dies_black (square) )
                            return 0;
                    }
                }
                else
                {
                    for (j=-1 ; j<2 ; j++)
                    {
                        square = board->m[lin+i][col+j];
                        if ( verify_tile_dies_black (square) )
                            return 0;
                    }
                }
            }
            return 1;
        }
    }
    else                /*WHITE TILES VERIFICATION PART*/
    {
        if (dir == 1)
        {
           for (i=-2 ; i<0 ; i++) 
           {
               if (i == -2)
               {
                   for (j=-2 ; j<3 ; j++)
                   {
                       square = board->m[lin+i][col+j];
                       if ( verify_tile_dies_white (square) )
                           return 0;
                   }
               }
               else
               {
                   for (j=-1 ; j<2 ; j++)
                   {
                       square = board->m[lin+i][col+j];
                       if ( verify_tile_dies_white (square) )
                           return 0;
                   }
               }
           }
           return 1;
        }
        else if (dir == 2)
        {
            for (j=-2 ; j<0 ; j++)
            {
                if (j == -2)
                {
                    for (i=-2 ; i<3 ; i++)
                    {
                        square = board->m[lin+i][col+j];
                        if ( verify_tile_dies_white (square) )
                            return 0;
                    }
                }
                else
                {
                    for (i=-1 ; i<2 ; i++)
                    {
                        square = board->m[lin+i][col+j];
                        if ( verify_tile_dies_white (square) )
                            return 0;
                    }
                }
            }
            return 1;
        }
        else if (dir == 3)
        {
            for (j=1 ; j<3 ; i++) 
            {
                if (j == 2)
                {
                    for (i=-2 ; i<3 ; i++)
                    {
                        square = board->m[lin+i][col+j];
                        if ( verify_tile_dies_white (square) )
                            return 0;
                    }
                }
                else
                {
                    for (i=-1 ; i<2 ; i++)
                    {
                        square = board->m[lin+i][col+j];
                        if ( verify_tile_dies_white (square) )
                            return 0;
                    }
                }
            }
            return 1;
        }
        else
        {
            for (i=1 ; i<3 ; i++) 
            {
                if (i == 2)
                {
                    for (j=-2 ; j<3 ; j++)
                    {
                        square = board->m[lin+i][col+j];
                        if ( verify_tile_dies_white (square) )
                            return 0;
                    }
                }
                else
                {
                    for (j=-1 ; j<2 ; j++)
                    {
                        square = board->m[lin+i][col+j];
                        if ( verify_tile_dies_white (square) )
                            return 0;
                    }
                }
            }
            return 1;
        }
    }
}

void fire_threatens (t_board *board,int lin,int col,int dir,int player)
{
    int i,j;
    if (! player)
    {
            if (dir == 1)       
            {
                for (i=-2 ; i<0 ; i++)          
                {
                    if (i == -2)
                    {
                        for (j=-2 ; j<3 ; j++)
                        {
                            board->m[lin+i][col+j]->th_white++;
                        }
                    }
                    else
                    {
                        for (j=-1 ; j<2 ; j++)
                        {
                            board->m[lin+i][col+j]->th_white++;
                        }
                    }
                }
            }
            else if (dir == 2)
            {
                for (j=-2 ; j<0 ; j++)              
                {
                    if (j == -2)
                    {
                        for (i=-2 ; i<3 ; i++)
                        {
                            board->m[lin+i][col+j]->th_white++; 
                        }
                    }
                    else
                    {
                        for (i=-1 ; i<2 ; i++)
                        {
                            board->m[lin+i][col+j]->th_white++;
                        }
                    }
                }
            }
            else if (dir == 3)
            {
                for (j=1 ; j<3 ; j++)          
                {
                    if (j == 2)
                    {
                        for (i=-2 ; i<3 ; i++)
                        {
                            board->m[lin+i][col+j]->th_white++;
                        }
                    }
                    else
                    {
                        for (i=-1 ; i<2 ; i++)
                        {
                            board->m[lin+i][col+j]->th_white++;
                        }
                    }
                }
            }
            else
            {
                for (i=1 ; i<3 ; i++)          
                {
                    if (i == 2)
                    {
                        for (j=-2 ; j<3 ; j++)
                        {
                            board->m[lin+i][col+j]->th_white++;
                        }
                    }
                    else
                    {
                        for (j=-1 ; j<2 ; j++)
                        {
                            board->m[lin+i][col+j]->th_white++;
                        }
                    }
                }
            }
    }
    else
    {
           if (dir == 1)       
           {
                for (i=-2 ; i<0 ; i++)          
                {
                    if (i == -2)
                    {
                        for (j=-2 ; j<3 ; j++)
                        {
                            board->m[lin+i][col+j]->th_black++;
                        }
                    }
                    else
                    {
                        for (j=-1 ; j<2 ; j++)
                        {
                            board->m[lin+i][col+j]->th_black++;
                        }
                    }
                }
           }
           else if (dir == 2)
           {
                for (j=-2 ; j<0 ; j++)          
                {
                    if (j == -2)
                    {
                        for (i=-2 ; i<3 ; i++)
                        {
                             board->m[lin+i][col+j]->th_black++;  
                        }
                    }
                    else
                    {
                        for (i=-1 ; i<2 ; i++)
                        {
                            board->m[lin+i][col+j]->th_black++;
                        }
                    }
                }
           }
           else if (dir == 3)
           {
                for (j=1 ; j<3 ; j++)          
                {
                    if (j == 2)
                    {
                        for (i=-2 ; i<3 ; i++)
                        {
                            board->m[lin+i][col+j]->th_black++;
                        }
                    }
                    else
                    {
                        for (i=-1 ; i<2 ; i++)
                        {
                            board->m[lin+i][col+j]->th_black++;
                        }
                    }
                }
           }
           else
           {
                for (i=1 ; i<3 ; i++)          
                {
                    if (i == 2)
                    {
                        for (j=-2 ; j<3 ; j++)
                        {
                            board->m[lin+i][col+j]->th_black++;
                        }
                    }
                    else
                    {
                        for (j=-1 ; j<2 ; j++)
                        {
                            board->m[lin+i][col+j]->th_black++;
                        }
                    }
                }
           }
    }
}

void bow_threatens (t_board *board,int lin,int col,int dir,int player)
{
    int i;
    if (! player)
    {
        if (dir == 1)       
        {
            for (i=2 ; i<5 ; i++)                    
            {
                if (lin-i >= 0)
                    board->m[lin-i][col]->th_white++;
            }
        }
        else if (dir == 2)
        {
            for (i=2 ; i<5 ; i++)                    
            {
                if (col-i >= 0)
                    board->m[lin][col-i]->th_white++;
            }
        }
        else if (dir == 3)
        {
            for (i=2 ; i<5 ; i++)                    
            {
                if (col+i <= 13)
                    board->m[lin][col+i]->th_white++;
            }
        }
        else
        {
            for (i=2 ; i<5 ; i++)                    
            {
                if (lin+i <= 13)
                    board->m[lin+i][col]->th_white++;
            }
        }
    }
    else
    {
        if (dir == 1)       
        {
            for (i=2 ; i<5 ; i++)                    
            {
                if (lin-i >= 0)
                    board->m[lin-i][col]->th_black++;
            }
        }
        else if (dir == 2)
        {
            for (i=2 ; i<5 ; i++)                    
            {
                if (col-i >= 0)
                    board->m[lin][col-i]->th_black++;
            }
        }
        else if (dir == 3)
        {
            for (i=2 ; i<5 ; i++)                    
            {
                if (col+i <= 13)
                    board->m[lin][col+i]->th_black++;
            }
        }
        else
        {
            for (i=2 ; i<5 ; i++)                    
            {
                if (lin+i <= 13)
                    board->m[lin+i][col]->th_black++;
            }
        }
    }
}

void sai_th_and_cv (t_board *board,int lin,int col,int dir,int player)
{
    if (! player)
    {
        if (dir == 1)                            
        {
            if (lin-1 >= 0)
                board->m[lin-1][col]->th_white++;
            if (col-1 >= 0)
                board->m[lin][col-1]->cv_white++;
            if (col+1 <= 13)
                board->m[lin][col+1]->cv_white++;
        }
        else if (dir == 2)
        {
            if (col-1 >= 0)
                board->m[lin][col-1]->th_white++;
            if (lin-1 >= 0)
                board->m[lin-1][col]->cv_white++;
            if (lin+1 <= 13)
                board->m[lin+1][col]->cv_white++;
        }
        else if (dir == 3)
        {
            if (col+1 <= 13)
                board->m[lin][col+1]->th_white++;
            if (lin+1 <= 13)
                board->m[lin+1][col]->cv_white++;
            if (lin-1 >= 0)
                board->m[lin-1][col]->cv_white++;
        }
        else
        {
            if (lin+1 <= 13)
                board->m[lin+1][col]->th_white++;
            if (col+1 <= 13)
                board->m[lin][col+1]->cv_white++;
            if (col-1 >= 0)
                board->m[lin][col-1]->cv_white++;
        }
    }
    else
    {
        if (dir == 1)                            
        {
            if (lin-1 >= 0)
                board->m[lin-1][col]->th_black++;
            if (col-1 >= 0)
                board->m[lin][col-1]->cv_black++;
            if (col+1 <= 13)
                board->m[lin][col+1]->cv_black++;
        }
        else if (dir == 2)
        {
            if (col-1 >= 0)
                board->m[lin][col-1]->th_black++;
            if (lin-1 >= 0)
                board->m[lin-1][col]->cv_black++;
            if (lin+1 <= 13)
                board->m[lin+1][col]->cv_black++;
        }
        else if (dir == 3)
        {
            if (col+1 <= 13)
                board->m[lin][col+1]->th_black++;
            if (lin+1 <= 13)
                board->m[lin+1][col]->cv_black++;
            if (lin-1 >= 0)
                board->m[lin-1][col]->cv_black++;
        }
        else
        {
            if (lin+1 <= 13)
                board->m[lin+1][col]->th_black++;
            if (col+1 <= 13)
                board->m[lin][col+1]->cv_black++;
            if (col-1 >= 0)
                board->m[lin][col-1]->cv_black++;
        }
    }
}

void air_threatens (t_board *board,int lin,int col,int player)
{
    if (! player)                              
    {
        if ((lin-2 >= 0 )&&(col-1 >= 0 ))
            board->m[lin-2][col-1]->th_white++;
        if ((lin-2 >= 0 )&&(col+1 <= 13))
            board->m[lin-2][col+1]->th_white++;
        if ((lin-1 >= 0 )&&(col-2 >= 0 ))
            board->m[lin-1][col-2]->th_white++;
        if ((lin-1 >= 0 )&&(col+2 <= 13))
            board->m[lin-1][col+2]->th_white++;
        if ((lin+1 <= 13)&&(col-2 >= 0 ))
            board->m[lin+1][col-2]->th_white++;
        if ((lin+1 <= 13)&&(col+2 <= 13))
            board->m[lin+1][col+2]->th_white++;
        if ((lin+2 <= 13)&&(col-1 >= 0 ))
            board->m[lin+2][col-1]->th_white++;
        if ((lin+2 <= 13)&&(col+1 <= 13))
            board->m[lin+2][col+1]->th_white++;
    }
    else
    {
        if ((lin-2 >= 0 )&&(col-1 >= 0 ))
            board->m[lin-2][col-1]->th_black++;
        if ((lin-2 >= 0 )&&(col+1 <= 13))
            board->m[lin-2][col+1]->th_black++;
        if ((lin-1 >= 0 )&&(col-2 >= 0 ))
            board->m[lin-1][col-2]->th_black++;
        if ((lin-1 >= 0 )&&(col+2 <= 13))
            board->m[lin-1][col+2]->th_black++;
        if ((lin+1 <= 13)&&(col-2 >= 0 ))
            board->m[lin+1][col-2]->th_black++;
        if ((lin+1 <= 13)&&(col+2 <= 13))
            board->m[lin+1][col+2]->th_black++;
        if ((lin+2 <= 13)&&(col-1 >= 0 ))
            board->m[lin+2][col-1]->th_black++;
        if ((lin+2 <= 13)&&(col+1 <= 13))
            board->m[lin+2][col+1]->th_black++;
    }
}

void earth_threatens (t_board *board,int lin,int col,int player)
{
    if (! player)                              
    {
        if (lin-2 >= 0 )
            board->m[lin-2][col]->th_white++;
        if (lin-1 >= 0 )
            board->m[lin-1][col]->th_white++;
        if (lin+1 <= 13)
            board->m[lin+1][col]->th_white++;
        if (lin+2 <= 13)
            board->m[lin+2][col]->th_white++;
        if (col-2 >= 0 )
            board->m[lin][col-2]->th_white++;
        if (col-1 >= 0 )
            board->m[lin][col-1]->th_white++;
        if (col+1 <= 13)
            board->m[lin][col+1]->th_white++;
        if (col+2 <= 13)
            board->m[lin][col+2]->th_white++;
    }
    else
    {
        if (lin-2 >= 0 )
            board->m[lin-2][col]->th_black++;
        if (lin-1 >= 0 )
            board->m[lin-1][col]->th_black++;
        if (lin+1 <= 13)
            board->m[lin+1][col]->th_black++;
        if (lin+2 <= 13)
            board->m[lin+2][col]->th_black++;
        if (col-2 >= 0 )
            board->m[lin][col-2]->th_black++;
        if (col-1 >= 0 )
            board->m[lin][col-1]->th_black++;
        if (col+1 <= 13)
            board->m[lin][col+1]->th_black++;
        if (col+2 <= 13)
            board->m[lin][col+2]->th_black++;
    }
}

void sword_threatens (t_board *board,int lin,int col,int player)
{
    int i,j;
    if (! player)
    {
        for (i=-1 ; i<2 ; i++)                                                      
        {
            for (j=-1 ; j<2 ; j++)
            {
                if (! ((i == 0)&&(j == 0)))
                {
                    if ((lin+i >= 0)&&(lin+i <= 13)&&(col+j >= 0)&&(col+j <= 13))
                        board->m[lin+i][col+j]->th_white++;
                }
            }
        }
    }
    else
    {
        for (i=-1 ; i<2 ; i++)                                                      
        {
            for (j=-1 ; j<2 ; j++)
            {
                if (! ((i == 0)&&(j == 0)))
                {
                    if ((lin+i >= 0)&&(lin+i <= 13)&&(col+j >= 0)&&(col+j <= 13))
                        board->m[lin+i][col+j]->th_black++;
                }
            }
        }
    }                                                                               
}

void water_th_and_cv (t_board *board,int lin,int col,int player)
{
    int i,j;
    if (! player)
    {
        for (i=-1 ; i<2 ; i++)                                                      
        {
            for (j=-1 ; j<2 ; j++)
            {
                if (! ((i == 0)&&(j == 0)))
                {
                    if ((lin+i >= 0)&&(lin+i <= 13)&&(col+j >= 0)&&(col+j <= 13))
                    {
                        if ((i == 0) || (j == 0))
                            board->m[lin+i][col+j]->cv_white++;
                        else
                            board->m[lin+i][col+j]->th_white++;
                    }
                }
            }
        }
    }
    else
    {
        for (i=-1 ; i<2 ; i++)                                                      
        {
            for (j=-1 ; j<2 ; j++)
            {
                if (! ((i == 0)&&(j == 0)))
                {
                    if ((lin+i >= 0)&&(lin+i <= 13)&&(col+j >= 0)&&(col+j <= 13))
                    {
                        if ((i == 0) || (j == 0))
                            board->m[lin+i][col+j]->cv_black++;
                        else
                            board->m[lin+i][col+j]->th_black++;
                    }
                }
            }
        }
    }                                                                               
}

int test_thread (t_board *board,int lin,int col,int player)
{
    if ( ((player) && (board->m[lin][col]->th_white >= 1)) || ((!player) && (board->m[lin][col]->th_black >= 1)) )
        return 1;
    else
        return 0;
}

int deploy_tile (t_board *board,int player,int *hand)
{
    int tile;
    scanw("%d", &tile);	/*picks the tile that the player want to dpeloy*/
    if (! tile )		/*type zero and cancel the deploy*/
        return 0;
    else if (!(tile > 0)&&(tile < 9))	/*if insn't a vaiable tile*/
        return 0;
    else if (hand[tile-1] == 0)	/*if the player doesn't have a tile of this type*/
        return 0;
    else
    {
        int lin,col;
        scanw("%d %d", &lin, &col);	/*picks the coordinate to deploy the tile on the board*/
        lin--;
        col--;
        if ((lin==-1) || (col==-1))		/*type zero and cancel the deploy*/
            return 0;
        else if (! ((lin < 14)&&(lin >= 0) && (col < 14)&&(col >= 0) && (col+lin >= 6)&&(col+lin <= 20) && (col-lin <= 7)&&(col-lin >= -7)) )	/*tests if it's on the board*/
            return 0;
        else if (! (((player)&&((board->m[lin][col]->th_black >= 1)||((lin < 7)&&(col > 6)))) || ((! player)&&((board->m[lin][col]->th_white >= 1)||((lin > 6)&&(col < 7)))))) /*tests if the square has friendly threat or it's on the base*/
            return 0;
        else
        {
            if (tile == 5)	/*if the player wants to deploy a lotus*/
            {
                if ((board->m[lin][col]->tile == EMPTY) || (board->m[lin][col]->tile == BLACKSQR))  /*lotus can be deployed on the black squares*/
                {
                    if ( test_thread (board,lin,col,player))   /*testes if the square has threat*/
                        return 0;
                    else
                    {
                        board->m[lin][col]->tile = 20+32*player;
                        int i,j;
                        for (i=-1 ; i<2 ; i++)
                        {
                            for (j=-1 ; j<2 ; j++)
                            {
                                if (player)
                                    board->m[lin+i][col+j]->cv_white = 1;
                                else
                                    board->m[lin+1][col+j]->cv_black = 1;
                            }
                        }
                        hand[tile-1]--;
                        return 1;
                    }
                }
                else
                    return 0;
            }
            else if (tile == 4)	/*if the player wants to deploy a fire*/ 
            {
                if (board->m[lin][col]->tile == EMPTY)
                {
                    if ( test_thread (board,lin,col,player) )  /*test if the square has threat*/
                        return 0;
                    else
                    {
                        int dir;
                        scanw("%d", &dir);	/*picks the direction that the player wants to puts the fire*/
                        if (! dir)          /*if picks zero, cancels the deploy*/
                            return 0;
                        else if (! ((dir > 0)&&(dir <5)) )  /*if is a vaiable direction*/
                            return 0;
                        else if (! verify_fire (board,lin,col,dir,player))    /*if the fire doesn't kills any piece*/
                            return 0;
                        else
                        {
                            board->m[lin][col]->tile = 16+32*player+(dir-1);         /*puts fire on de square*/
                            fire_threatens (board,lin,col,dir,player);      /*puts the threaten of the fire*/
                            hand[tile-1]--;
                            return 1;
                        }
                    }
                }
                else
                    return 0;
            }
            else
            {
                if (board->m[lin][col]->tile == EMPTY)
                {
                    if ( test_thread (board,lin,col,player) )  /*testes if the square has threat*/
                        return 0;
                    else
                    {
                        if ((tile == 2)||(tile == 6))   /*tiles that can rotate*/
                        {
                            int dir;
                            scanw("%d", &dir);
                            if (!dir)
                                return 0;
                            else if (! ((dir > 0)&&(dir < 5)) )
                                return 0;
                            else
                            {
                                if (tile == 2)  /*if player wants to deploy a bow*/
                                {
                                    bow_threatens (board,lin,col,dir,player);
                                    board->m[lin][col]->tile = 8+32*player+(dir-1);
                                    hand[tile-1]--;
                                    return 1;
                                }
                                else            /*if player wants to deploy a sai*/
                                {
                                    sai_th_and_cv (board,lin,col,dir,player);
                                    board->m[lin][col]->tile = 24+32*player+(dir-1);
                                    hand[tile-1]--;
                                    return 1;
                                }
                            }
                        }
                        else        /*tiles that cannot rotate*/
                        {
                            if (tile == 1)      /*if player wants to deploy a air*/
                            {
                                air_threatens (board,lin,col,player);
                                board->m[lin][col]->tile = 4+32*player;
                                hand[tile-1]--;
                                return 1;
                            }
                            else if (tile == 3) /*if player wants to deploy a earth*/
                            {
                                earth_threatens (board,lin,col,player);
                                board->m[lin][col]->tile = 12+32*player;
                                hand[tile-1]--;
                                return 1;
                            }
                            else if (tile == 7) /*if player wants to deploy a sword*/
                            {
                                sword_threatens (board,lin,col,player);
                                board->m[lin][col]->tile = 28+32*player;
                                hand[tile-1]--;
                                return 1;
                            }
                            else                /*if player wants to deploy a water*/
                            {
                                water_th_and_cv (board,lin,col,player);
                                board->m[lin][col]->tile = 32+32*player;
                                hand[tile-1]--;
                                return 1;                                 
                            }
                        } 
                    }
                }
                else
                    return 0;
            } 
        }
    }	
}

void print_debug (WINDOW *wdebug1,WINDOW *wdebug2,t_board *board)
{
    int i,j;
    for (i=0 ; i<7 ; i++)
    {
        for (j=0 ; j<14 ; j++)
        {
            mvwprintw (wdebug1,1+i*6  ,5+j*3 ,"%d",board->m[i][j]->tile);
            mvwprintw (wdebug1,1+i*6+1,5+j*3 ,"%d",board->m[i][j]->th_white);
            mvwprintw (wdebug1,1+i*6+2,5+j*3 ,"%d",board->m[i][j]->th_black);
            mvwprintw (wdebug1,1+i*6+3,5+j*3 ,"%d",board->m[i][j]->cv_white);
            mvwprintw (wdebug1,1+i*6+4,5+j*3 ,"%d",board->m[i][j]->cv_black);
        }
    }
    for (i=7 ; i<14 ; i++)                                                       
    {
        for (j=0 ; j<14 ; j++)
        {
            mvwprintw (wdebug2,1+(i-7)*6  ,5+j*3 ,"%d",board->m[i][j]->tile);
            mvwprintw (wdebug2,1+(i-7)*6+1,5+j*3 ,"%d",board->m[i][j]->th_white);
            mvwprintw (wdebug2,1+(i-7)*6+2,5+j*3 ,"%d",board->m[i][j]->th_black);
            mvwprintw (wdebug2,1+(i-7)*6+3,5+j*3 ,"%d",board->m[i][j]->cv_white);
            mvwprintw (wdebug2,1+(i-7)*6+4,5+j*3 ,"%d",board->m[i][j]->cv_black);
        }
    }                                                                                                                                            
    box (wdebug1,0,0);
    box (wdebug2,0,0);
    wrefresh(wdebug1);
    wrefresh(wdebug2);
}

void print_deploy_msg (WINDOW *wboard)
{
    mvwprintw (wboard, 37 , 2  , "Write the number of");
    mvwprintw (wboard, 38 , 2  , "the tile that you want");         
    mvwprintw (wboard, 39 , 2  , "to deploy, the position");
    mvwprintw (wboard, 40 , 2  , "on the board and, if the tile");
    mvwprintw (wboard, 41 , 2  , "can rotate, his rotation.");
    mvwprintw (wboard, 42 , 2  , "Type 0 to cancel the action.");
    mvwprintw (wboard, 37 , 47 , "For the directions:");            
    mvwprintw (wboard, 38 , 47 , "1 - Up");       
    mvwprintw (wboard, 39 , 47 , "2 - Left");
    mvwprintw (wboard, 40 , 47 , "3 - Right");
    mvwprintw (wboard, 41 , 47 , "4 - Down");
    wrefresh  (wboard);
}

int main ()
{
    initscr();
    WINDOW *wboard    = newwin (44,72,0,0);
    WINDOW *whand     = newwin (44,20,0,72);
    WINDOW *wreserve  = newwin (44,20,0,92);
    WINDOW *wdebug1   = newwin (44,50,0,112);
    WINDOW *wdebug2   = newwin (44,50,0,162);
    refresh();
    noecho();
    curs_set(FALSE);

    start_color();

    init_color(10,1000,600 ,0   );			/*Orange*/
    init_color(11,400 ,400 ,0   );			/*Brown*/
    init_color(12,400 ,0   ,400 );			/*Purple*/
    init_color(13,600 ,600 ,600 );			/*Grey*/
    init_color(14,150 ,150 ,150 );			/*Ligthier black*/
    init_color(15,400 ,400 ,400 );          /*Light black*/
    init_color(COLOR_BLACK, 0 , 0 , 0 );
    init_pair(1,COLOR_GREEN   ,COLOR_BLACK);
    init_pair(2,10            ,COLOR_BLACK);
    init_pair(3,13            ,COLOR_BLACK);

    init_pair(10,COLOR_CYAN	  ,COLOR_BLACK);	/*Air color*/
    init_pair(11,11		      ,COLOR_BLACK);	/*Bow color*/
    init_pair(12,COLOR_GREEN  ,COLOR_BLACK);	/*Earth color*/
    init_pair(13,COLOR_RED	  ,COLOR_BLACK);	/*Fire color*/
    init_pair(14,COLOR_MAGENTA,COLOR_BLACK);	/*Lotus color*/
    init_pair(15,12		      ,COLOR_BLACK);	/*Sai color*/
    init_pair(16,13		      ,COLOR_BLACK);	/*Sword color*/
    init_pair(17,COLOR_BLUE   ,COLOR_BLACK);	/*Water color*/
    init_pair(18,14		      ,COLOR_BLACK);	/*Black square color*/
    init_pair(19,15           ,COLOR_BLACK);    /*Black tiles color*/
    init_pair(20,COLOR_WHITE  ,COLOR_BLACK);    /*White tiles color*/

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

    initializes_t	  (tiles);
    initializes_v	  (hv_white,hv_black,0);
    initializes_v	  (rv_white,rv_black,3);
    initializes_board (&board);

    while (! finish)
    {
        print_board 	  (wboard,&board);
        print_vector	  (whand   ,hv_white,hv_black,tiles);
        print_vector	  (wreserve,rv_white,rv_black,tiles);
        print_debug       (wdebug1,wdebug2,&board);
        char k = getch();
        if (k == 'b') 	/*makes buy tiles*/
        {
            print_buy_msg (wboard);
            if (! player)
            {
                if ( buy_tiles (hv_white,rv_white) )
                    player = (player + 1)%2;
            }
            else
            {
                if ( buy_tiles (hv_black,rv_black) )
                    player = (player + 1)%2;
            }
        }
        else if (k == 'm')
        {
            /*makes maves tiles*/
        }
        else if (k == 'd')	/*makes deploy tiles*/
        {
            print_deploy_msg (wboard);
            if (! player)
            {
                if (deploy_tile (&board,player,hv_white))
                    player = (player + 1)%2;
            }
            else
            {
                if (deploy_tile (&board,player,hv_black))
                    player =( player + 1)%2;
            }
        }
        else if (k == 'q')
            finish = 1;
    }	
    endwin();
    return 1;
}
