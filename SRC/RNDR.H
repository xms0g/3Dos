#ifndef RENDERER_H
#define RENDERER_H

void rndPutchar(int x, int y, char color, const int (*font)[5][5]);

void rndDDA(int x0, int y0, int x1, int y1, char color);
    
void rndBresenham(int x0, int y0, int x1, int y1, char color);

void rndDrawRect(int x, int y, int width, int height, char color);
    
void rndDrawTri(int x0, int y0, int x1, int y1, int x2, int y2, char color);

void rndDrawFilledTri(int x0, int y0, int x1, int y1, int x2, int y2, char color);

#endif