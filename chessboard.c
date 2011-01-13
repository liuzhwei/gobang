
#include <stdio.h>
#include "main.h"

#define Starting_X 100
#define Starting_Y 40
#define Space      30 
#define Size_X     30
#define Size_Y     24

void print_chessman(int x, int y, int r, u32_t color);


void print_board(void)
{
	int i = 0; 
	
	for(i = 0; i < Size_X; i++)
	{
		fb_line(Starting_X+Space*i, Starting_Y, Starting_X+Space*i, Starting_Y+Space*(Size_Y-1), 0x0000ff00);	
	}
	for(i = 0; i < Size_Y; i++)
	{
		fb_line(Starting_X, Starting_Y+Space*i, Starting_X+Space*(Size_X-1), Starting_Y+Space*i, 0x0000ff00);	
	}
}




void find_location(int x, int y, u32_t color)
{
	int x1 = 0, y1 = 0, i = 0;
	while(Starting_X+i*Space <= x)
	{
		i++;
	}
	x1 = (((Starting_X + i*Space - x) >= (x - Starting_X - (i-1)*Space)) ? Starting_X + (i-1)*Space : Starting_X + i*Space);
	
	i = 0;
	while(Starting_Y+i*Space <= y)
	{
		i++;
	}
	y1 = (((Starting_Y + i*Space - y) >= (y - Starting_Y - (i-1)*Space)) ? Starting_Y + (i-1)*Space : Starting_Y + i*Space);
	
	print_chessman(x1,y1,12,color);
}


/* *
   * draw and fill a circle
   * */
void print_chessman(int x, int y, int r, u32_t color)
{
	int i = 0, j = 0;

	for(i = x-r; i <= x+r; i++)
	{
		for(j = y-r; j <= y+r; j++)
		{
			if((x-i)*(x-i) + (y-j)*(y-j) <= r*r)
			{
				fb_one_pixel(i,j,color);
			}
		}
	}
}



void drow_background(u32_t color)
{
	int i = 0;

	for(i = 0; i < (Size_Y-1)*Space; i++)
	{
		fb_line(Starting_X, Starting_Y+i, Starting_X + (Size_X-1)*Space, Starting_Y+i,color);
	}
}
