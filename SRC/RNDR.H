#ifndef RENDERER_H
#define RENDERER_H

void rndPutchar(int x, int y, unsigned char color, const int (*font)[5][5]);

void rndDDA(int x0, int y0, int x1, int y1, unsigned char color);
    
void rndBresenham(int x0, int y0, int x1, int y1, unsigned char color);

void rndDrawRect(int x, int y, int width, int height, unsigned char color);
    
void rndDrawTri(int x0, int y0, int x1, int y1, int x2, int y2, unsigned char color);

void rndDrawFilledTri(int x0, int y0, int x1, int y1, int x2, int y2, unsigned char color);

#endif