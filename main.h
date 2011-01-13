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


typedef struct
{
	int dx;       // mice move left and right
	int dy;       // mice move up and down
	int dz;       // mice wheel
	int button;
} m_event_t;



extern int  fb_line(int x1, int y1, int x2, int y2, u32_t color);
extern int fb_circle(int x0, int y0, int r, u32_t color);

extern int fb_one_pixel(int x,int y,u32_t color);
extern void print_board(u32_t color);
extern void find_location(int x, int y, u32_t color);
extern void drow_background(u32_t color);
extern int draw_cursor(int x, int y);
extern int restore_shape(int x, int y);
extern void print_chessman(int x, int y, int r, u32_t color);


extern int mouse_doing(void);


#endif
