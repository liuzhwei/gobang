#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <unistd.h>
#include "main.h"

v_info_t fb_v;

void create_scr_fb(void)
{
    int fd;
    struct fb_var_screeninfo fb_var;
    u32_t *p = NULL;

    fd = open("/dev/fb0", O_RDWR);
    if (fd < 0) 
    {
        perror("open");
        exit(1);
    }

    if (ioctl(fd, FBIOGET_VSCREENINFO, &fb_var) < 0)
    {
        perror("ioctl");
        exit(1);
    }

    fb_v.w = fb_var.xres;
    fb_v.h = fb_var.yres;
    fb_v.bpp = fb_var.bits_per_pixel;

    printf("w = %d\th = %d\tbpp = %d\n",fb_v.w, fb_v.h, fb_v.bpp);

    p = mmap(NULL, fb_v.w*fb_v.h*fb_v.bpp/8,PROT_WRITE|PROT_READ, MAP_SHARED, fd, 0);
    if (p == MAP_FAILED) 
    {
        perror("map");
        exit(1);
    }
    *p = 0x00ff0000; 
	fb_v.fb_mem = p;
	close(fd);
}

int fb_one_pixel(int x,int y,u32_t color)
{
	u32_t *p = fb_v.fb_mem;
	p[x+y*fb_v.w] = color;
	return 0;
}
int main(int argc, const char *argv[])
{
	int i = 0, j = 0;
	u32_t color;

    create_scr_fb();
	drow_background(0x000000ff);
	print_board();
	for(i = 0; i < 24; i++)
	{
		for(j = 0;j < 30; j++)
		{
			if((j+i)%2 == 0)
				color = 0x00ff0000;
			else
				color = 0x00ffff00;
			find_location(100 + 30*j, 40 + 30*i,color);
		}
	}
//	for(i = 0; i < 10; i++)
	{
		fb_circle(500,300,100, 0x00000000);
	}

    return 0;
}
