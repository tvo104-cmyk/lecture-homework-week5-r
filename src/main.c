#include "defines.h"
#include "uart.h"
#include "vid.h"

UART* up;

int show_bmp(char* p, int start_row, int start_col) {  // SAME as before
  int h, w, pixel, rsize, i, j;
  unsigned char r, g, b;
  char* pp;
  int* q = (int*)(p + 14);  // skip over 14-byte file header
  w = *(q + 1);             // image width in pixels
  h = *(q + 2);             // image height in pixels
  p += 54;                  // p-> pixels in image
  // BMP images are upside down, each row is a multiple of 4 bytes
  rsize = 4 * (w + 0);   // multiple of 4
  p += (h - 1) * rsize;  // last row of pixels
  for (i = start_row; i < start_row + h; i++) {
    pp = p;
    for (j = start_col; j < start_col + w; j++) {
      b = *pp;
      g = *(pp + 1);
      r = *(pp + 2);                     // BRG values
      pixel = (b << 16) | (g << 8) | r;  // pixel value
      fb[i * WIDTH + j] = pixel;         // write to frame buffer
      pp += 4;                           // advance pp to next pixel
    }
    p -= rsize;  // to preceding row
  }
  uprintf(up, "\nBMP image height=%d width=%d\n", h, w);
}

int main() {
  char line[64];
  fbuf_init();
  setpos(13, 0);

  uart_init();
  up = &uart[0];

  char* p = &_binary____image0_bmp_start;
  show_bmp(p, 0, 0);  // display a logo

  while (1) {
    color = GREEN;
    kprintf("enter a line from UART port : ");
    uprintf(up, "enter line from UART : ");
    ugets(up, line);
    uprintf(up, " line=%s\n", line);
    color = RED;
    kprintf("line=%s\n", line);
  }
}