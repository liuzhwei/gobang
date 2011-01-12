
#include <stdio.h>
#include "main.h"

#define Starting_X 100
#define Starting_Y 40
#define Space      30 
#define Size_X     30
#define Size_Y     24

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
