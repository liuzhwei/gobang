

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <fcntl.h>
#include "main.h"



#define C_WIDTH 10
#define C_HEIGHT 17
#define T__      0x00ffb5c5
#define BORD     0x0
#define X__      0x00ff

extern v_info_t fb_v;


static u32_t cursor_pixel[C_WIDTH * C_HEIGHT] = {
	BORD, T__, T__, T__, T__, T__, T__, T__, T__, T__,
	BORD, BORD, T__, T__, T__, T__, T__, T__, T__, T__,
	BORD, X__, BORD, T__, T__, T__, T__, T__, T__, T__,
	BORD, X__, X__, BORD, T__, T__, T__, T__, T__, T__,
	BORD, X__, X__, X__, BORD, T__, T__, T__, T__, T__,
	BORD, X__, X__, X__, X__, BORD, T__, T__, T__, T__,
	BORD, X__, X__, X__, X__, X__, BORD, T__, T__, T__,
	BORD, X__, X__, X__, X__, X__, X__, BORD, T__, T__,
	BORD, X__, X__, X__, X__, X__, X__, X__, BORD, T__,
	BORD, X__, X__, X__, X__, X__, X__, X__, X__, BORD,
	BORD, X__, X__, X__, X__, X__, BORD, BORD, BORD, BORD,
	BORD, X__, X__, BORD, X__, X__, BORD, T__, T__, T__,
	BORD, X__, BORD, T__, BORD, X__,X__, BORD, T__, T__,
	BORD, BORD, T__, T__, BORD, X__,X__, BORD, T__, T__,
	T__, T__, T__, T__, T__, BORD, X__, X__, BORD, T__,
	T__, T__, T__, T__, T__, BORD, X__, X__, BORD, T__,
	T__, T__, T__, T__, T__, T__, BORD, BORD, T__, T__
};

static u32_t shape_save[C_WIDTH * C_HEIGHT] ;



int save_shape(int x, int y)
{
	int i = 0, j = 0;
	u32_t *p = fb_v.fb_mem;

	for(i = 0; i < C_HEIGHT; i++)
		for(j = 0; j < C_WIDTH; j++)
			shape_save[j + i*C_WIDTH] = p[x + j + (y+i)*fb_v.w];

	return 0;
}

int restore_shape(int x, int y)
{
	int i = 0, j = 0;

	for(i = 0; i < C_HEIGHT; i++)
		for(j = 0; j < C_WIDTH; j++)
			fb_one_pixel(x+j, y+i, shape_save[j + i*C_WIDTH]);
	
	return 0;
}

int draw_cursor(int x, int y)
{
	int i = 0, j = 0;
	u32_t color;

	save_shape(x,y);


	for(i = 0; i < C_HEIGHT; i++)
	{
		for(j = 0; j < C_WIDTH; j++)
		{
			color = (cursor_pixel[j + i*C_WIDTH] == T__) ? shape_save[j + i*C_WIDTH] : cursor_pixel[j + i*C_WIDTH];
			fb_one_pixel(x+j, y+i,color);
		}
	}

	return 0;
}





int get_m_info(int fd, m_event_t * event)
{
	char buf[8] = {0};
	int n;

	n = read(fd, buf, 8);
	if(n <= 0)
	{
		return 0;
	}
	event -> button = (buf[0] & 0x07);
	event -> dx = buf[1];
	event -> dy = -buf[2];
	event -> dz = buf[3];

	return n;

}

int mouse_doing(void)
{
	m_event_t mevent;
	int fd;
	int mx = 512;
	int my = 384;

	u32_t color;
	char times = 1;

	fd = open("/dev/input/mice",O_RDWR | O_NONBLOCK);
	if(fd < 0)
	{
		perror("open");
		exit(1);
	}

	draw_cursor(mx,my);

	while(1)
	{
		if(get_m_info(fd,&mevent) > 0)
		{
			restore_shape(mx,my);

			mx += mevent.dx;
			my += mevent.dy;

			mx = ((mx >= 0) ? mx : 0);
			my = ((my >= 0) ? my : 0);
			if(mx >= (fb_v.w - C_WIDTH))
			{
				mx = (fb_v.w - C_WIDTH);
			}
			if(my >= (fb_v.h - C_HEIGHT))
			{
				my = (fb_v.h - C_HEIGHT);
			}

			switch(mevent.button)
			{
				case 1:
					if(times > 0)
					{
						color = 0x00000000;
						times = -times;
					}
					else 
					{
						color = 0x00ffffff;
						times = -times;
					}
					print_chessman(mx,my,13,color);
					save_shape(mx,my);
					usleep(10);
					
					break;
				case 2:
					
					break;
				case 4:
					
					break;
				default:
					break;
			}
			draw_cursor(mx,my);
		}
//	usleep(1000);
	}

}

#if 0

/* *  
 * return mice device fd
 *  return: 0 --- read mouse success
 *	   1 --- error for read mouse
 * */
int mouse_open(const char *mdev)
{
	if(mdev == NULL)
		mdev = "/dev/input/mice";
	return(open(mdev, O_RDWR | O_NONBLOCK));
}

#define READ_MOUSE 8
int mouse_parse(int fd, mevent_t * mevent)
{
	s8_t buf[READ_MOUSE];
	int n;
	if((n = read(fd, buf, READ_MOUSE)) > 0)
	{
		/* * *
		 * about n: 1. left key      2. right key
		 *          3. middle key    4. no button key
		 * */
		mevent -> button = buf[0] & 0x07;

		mevent -> dx = buf[1];
		mevent -> dy = -buf[2];
		mevent -> dz = buf[3];
	}
	else
		return -1;
	
	return 0;
}



int mouse_darw(const pinfo_t fb, int x, int y)
{
	int i = 0, j = 0;

	mouse_save(fb,x,y);

	for(j = 0; j < C_HEIGHT; j++)
		for(i = 0; i < C_WIDTH; i++)
			if(cursor_pixel[i + j*C_WIDTH] != T__)
				fb_pixel(fb, x+i, y+j)
}

#endif
