#ifndef _MAIN_H
#define _MAIN_H

#include <stdio.h>

typedef unsigned int  u32_t;
typedef unsigned char u8_t;

typedef struct 
{
    int w;
    int h;
    int bpp;
    void *fb_mem;
}v_info_t;


extern int  fb_line(int x1, int y1, int x2, int y2, u32_t color);
extern int fb_one_pixel(int x,int y,u32_t color);
extern void print_board(void);

#endif
