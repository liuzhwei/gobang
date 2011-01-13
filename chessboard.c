
#include <stdio.h>
#include "main.h"

#define Starting_X 100
#define Starting_Y 40
#define Space      30 
#define Size_X     30
#define Size_Y     24


void print_board(u32_t color)
{
	int i = 0; 
	
	for(i = 0; i < Size_X; i++)
	{
		fb_line(Starting_X+Space*i, Starting_Y, Starting_X+Space*i, Starting_Y+Space*(Size_Y-1), color);	
	}
	for(i = 0; i < Size_Y; i++)
	{
		fb_line(Starting_X, Starting_Y+Space*i, Starting_X+Space*(Size_X-1), Starting_Y+Space*i, color);	
	}
}



/* *
   * in this function, when we get a radom location.
   * we must correct the location to our chessmap line.
   * at last we print a chessmen on the net we darw.
   *
   * draw and fill a circle as a chessman
   * */
void print_chessman(int x, int y, int r, u32_t color)
{
	int i = 0, j = 0;
	int x1 = 0, y1 = 0;

	if(x > Starting_X-Space/2 && x < Starting_X+Size_X*Space-Space/2 && 
		y > Starting_Y-Space/2 && y < Starting_Y+Size_Y*Space-Space/2)
	{
		x1 = (x - Starting_X + Space/2) / Space * Space + Starting_X;
		y1 = (y - Starting_Y + Space/2) / Space * Space + Starting_Y;

		for(i = x1-r; i <= x1+r; i++)
		{
			for(j = y1-r; j <= y1+r; j++)
			{
				if((x1-i)*(x1-i) + (y1-j)*(y1-j) <= r*r)
				{
					fb_one_pixel(i,j,color);
				}
			}
		}
	}
}



#define BAR 10
void drow_background(u32_t color)
{
	int i = 0;

	for(i = 0 - BAR; i < (Size_Y-1)*Space + BAR; i++)
	{
		fb_line(Starting_X - BAR, Starting_Y+i, Starting_X + (Size_X-1)*Space + BAR, Starting_Y+i,color);
	}
}
