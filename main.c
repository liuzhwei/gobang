
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

void clear_screen(u32_t color)
{
	int i = 0, j = 0;
	
	for(i = 0; i < fb_v.h; i++)
	{
		for(j = 0; j < fb_v.w; j++)
		{
			fb_one_pixel(j,i,color);
		}
	}
}

int main(int argc, const char *argv[])
{

    create_scr_fb();

	clear_screen(0x008e388e);
	drow_background(0x00ffb5b5);
	print_board(0x001874cd);
	print_circle(50,100,25,0x00000000);
	print_circle(50,170,25,0x00ffffff);

	mouse_doing();

    return 0;
}
