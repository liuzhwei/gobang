
#include <stdio.h>
#include "main.h"


char point_state[Size_X * Size_Y] = { 0 };



int correct_x(int x)
{
	return ((x - Starting_X + Space/2) / Space);
}

int correct_y(int y)
{
	return ((y - Starting_Y + Space/2) / Space);
}





int sign_point(int x, int y, char a)
{
	int i = 0;
	int j = 0;

	i = correct_x(x);
	j = correct_y(y);

	point_state[i + j*Size_X] = a;    // a is 1 or 2 :signed who place the chessman
//	printf("x = %d\ty = %d\twho = %d\n",i,j,point_state[i + j*Size_X])	;
	return 0;
}

int check_five(int x, int y)   
{
	int counter = 1;
	int i = 0;

	
	for(i = 1; i < 5; i++)            // to right
	{	
		if(Size_X-x < 5)
		{
			break;
		}
		if(point_state[x + y*Size_X] == point_state[x + i + y*Size_X])
		{
			counter++;
			if(counter == 5)
			{
				return (int)point_state[x + y*Size_X];
			}
		}
		else
		{
			counter = 1;
			break;
		}
	}

	for(i = 1; i < 5; i++)          // to down
	{
		if(Size_Y-y < 5)
		{
			break;
		}
		if(point_state[x + y*Size_X] == point_state[x + (y+i)*Size_X])
		{
			counter++;
			if(counter == 5)
			{
				return (int)point_state[x + y*Size_X];
			}
		}
		else
		{
			counter = 1;
			break;
		}
	}

	for(i = 1; i < 5; i++)          // to down_right
	{
		if((Size_X-x < 5) || (Size_Y-y < 5))
		{
			break;
		}
		if(point_state[x + y*Size_X] == point_state[x + i + (y+i)*Size_X])
		{
			counter++;
			if(counter == 5)
			{
				return (int)point_state[x + y*Size_X];
			}
		}
		else
		{
			counter = 1;
			break;
		}
	}

	for(i = 1; i < 5; i++)          // to up_right
	{
		if((Size_X-x < 5) || y<4)
		{
			break;
		}
		if(point_state[x + y*Size_X] == point_state[x + i + (y-i)*Size_X])
		{
			counter++;
			if(counter == 5)
			{
				return (int)point_state[x + y*Size_X];
			}
		}
		else
		{
			counter = 0;
			break;
		}
	}

	return 0;
}



int check_all(void)
{
	int i = 0, j = 0;

	for(i = 0; i < Size_Y; i++)
	{
		for(j = 0; j < Size_X; j++)
		{
			if(check_five(j,i) != 0)
			{
				printf(" ......1 is black, 2 is white .This time %d won........\n",check_five(j,i));
				return 1;
			}
		}
	}

	return 0;
}
