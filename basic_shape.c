
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "main.h"
#include <math.h>

/**
 *      change for two numbers
 **/
void swap(int *a, int *b) 
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}
/**
 *   program: print a line as every point of view
 *
 *   in the first step: printing from left and up to right and down with rat little 45 degree.
 *   in the second step : we can pringt line which from right to lift.
 *   in the third step: we can deal with condition of rating bigger than 45 degree.
 *
 ***/
int  fb_line(int x1, int y1, int x2, int y2, u32_t color)
{
	int dx = x2-x1;
	int dy = y2-y1;   // in common condition must be " dy < dx "
	int inc = ((dx*dy > 0) ? 1 : -1); // one: from down to up
	int p = 0;

	if(abs(dx) > abs(dy))
	{
		if(dx < 0)         // two: deal with condition of " dx < 0 " , and we can print for right to lift.
		{
			swap(&x1, &x2);
			swap(&y1, &y2);
			dx = -dx;
			dy = -dy;
		}

		p =2*dy-dx;
		dy = abs(dy);     //  one: deal with condition of " dy < 0 " , and we can print from down to up.
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
	}
	else
	{
		if(dy < 0)
		{
				
			swap(&x1, &x2);
			swap(&y1, &y2);
			dx = -dx;
			dy = -dy;
		}

		p = 2*dx - dy;
		dx = abs(dx);
		while(y1 <= y2)
		{
			fb_one_pixel(x1,y1,color);
			y1++;
			if(p < 0)
			{
				p += 2*dx;
			}
			else
			{
				p += 2*(dx-dy);
				x1 += inc;
			}
		}
	}
	return 0;

}
