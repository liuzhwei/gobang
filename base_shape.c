
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "main.h"
#include <math.h>

int  fb_line(int x1, int y1, int x2, int y2, u32_t color)
{
	int dx = x2-x1;
	int dy = y2-y1;
	int inc = ((dx*dy > 0 ? 1 : -1));
	int p =2*dy-dx;

	dy = abs(dy);
	while(x1<=x2)
	{
		fb_one_pixel(x1,y1,color);
		x1++;
		if(p< 0)
		{
			p += 2*dy;
			
		}
		else 
		{
			p += 2*(dy-dx);
			y1 += inc;
		
		}
	}
	return 0;

}
