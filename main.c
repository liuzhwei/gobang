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
extern const unsigned char girl[2949128];

void create_scr_fb(void)
{
    int fd;
    struct fb_var_screeninfo fb_var;
    u32_t *p = NULL;
    u32_t i;

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

    //p = mmap(NULL, fb_v.w*fb_v.h*fb_v.bpp/8,PROT_WRITE|PROT_READ, MAP_SHARED, fd, 0);
    p = mmap(NULL, 1208*1024*4,PROT_WRITE|PROT_READ, MAP_SHARED, fd, 0);
    if (p == MAP_FAILED) 
    {
        perror("map");
        exit(1);
    }
    //*p = 0x00ff0000; 
    //for (i = 0; i < 1351000; i++) 
    //for (i = 0; i < 1280*1024*4; i++) 
    //{
    ////p[i] = 0x00ff00ff;
    //*(p + i) = girl[i];
    //}
}

int main(int argc, const char *argv[])
{
    create_scr_fb();
    return 0;
}
