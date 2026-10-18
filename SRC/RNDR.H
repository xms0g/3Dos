#ifndef RENDERER_H
#define RENDERER_H

void rnd_putchar(int x, int y, unsigned char color, const int (*font)[5][5]);

void rnd_dda(int x0, int y0, int x1, int y1, unsigned char color);
    
void rnd_bresenham(int x0, int y0, int x1, int y1, unsigned char color);

void rnd_draw_rect(int x, int y, int width, int height, unsigned char color);
    
void rnd_draw_tri(int x0, int y0, int x1, int y1, int x2, int y2, unsigned char color);

void rnd_draw_filled_tri(int x0, int y0, int x1, int y1, int x2, int y2, unsigned char color, double light_intensity);

#endif