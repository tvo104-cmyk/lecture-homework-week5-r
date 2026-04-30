#ifndef _VID_H_
#define _VID_H_
extern int fbuf_init();
extern int setpos(int r, int c);
extern unsigned char _binary_font_start[];
extern int volatile* fb;
extern char _binary____image0_bmp_start;
extern char _binary____image1_bmp_start;
extern int color;
extern int kprintf(char* fmt, ...);
extern int WIDTH;
extern int HEIGHT;
#endif