#include "rndr.h"
#include "vga.h"
#include "math.h"
#include "shdplt.h"

#define isTopLeft(x0, y0, x1, y1) ((y1 - y0) < 0 || ((y1 - y0) == 0 && (x1 - x0) > 0))
#define edgeFunction(x0, y0, x1, y1, x2, y2) ((x1 - x0) * (y2 - y0) - (y1 - y0) * (x2 - x0))

static double threshold(int x, int y) {
    static const int bayer4x4[16] = {
        0, 8, 2, 10,
        12, 4, 14, 6,
        3, 11, 1, 9,
        15, 7, 13, 5
    };

    return bayer4x4[((y & 3) << 2) | (x & 3)] * (1.0 / 16.0);
}

static unsigned char dithering(int x, int y, unsigned char color, double intensity) {
    double scaled = intensity * (SHADE_LEVELS - 1);
    int lo = floor(scaled);
    int hi = lo < SHADE_LEVELS - 1 ? ceil(scaled) : lo;

    double frac = scaled - lo;
    int level = frac > threshold(x, y) ? hi : lo;

    return shade_palette[color][level];
}

void rnd_putchar(int x, int y, unsigned char color, const int (*font)[5][5]) {
    int i, j;
    for (i = 0; i < 5; ++i) {
        for (j = 0; j < 5; ++j) {
            if ((*font)[j][i]) {
                _vga_put_pixel(x + i, y + j, color);
            }
        }
    }
}

void rnd_dda(int x0, int y0, int x1, int y1, unsigned char color) {
    int dx = x1 - x0;
    int dy = y1 - y0;

    int step = (abs(dx) >= abs(dy)) ? abs(dx) : abs(dy);

    float xinc = dx / (float)(step);
    float yinc = dy / (float)(step);

    float x = x0;
    float y = y0;

    int i;
    for (i = 0; i < step; ++i) {
        _vga_put_pixel(round(x), round(y), color);
        
        x += xinc;
        y += yinc;
    }
}

void rnd_bresenham(int x0, int y0, int x1, int y1, unsigned char color) {
    int dx = abs(x1 - x0);
    int sx = x0 < x1 ? 1 : -1;
    int dy = abs(y1 - y0);
    int sy = y0 < y1 ? 1 : -1; 
    int err = (dx > dy ? dx : -dy)/2;
    int e2;

    while (x0 != x1 || y0 != y1) {
        _vga_put_pixel(x0, y0, color);
        
        e2 = err;
        
        if (e2 > -dx) {
            err -= dy; 
            x0 += sx; 
        }

        if (e2 < dy) { 
            err += dx; 
            y0 += sy; 
        }
    }
}

void rnd_draw_rect(int x, int y, int width, int height, unsigned char color) {
    int i, j;
    for (i = 0; i < width; i++) {
        for (j = 0; j < height; j++) {
            _vga_put_pixel(x + i, y + j, color);
        }
    }
}

void rnd_draw_tri(int x0, int y0, int x1, int y1, int x2, int y2, unsigned char color) {
    rnd_bresenham(x0, y0, x1, y1, color);
    rnd_bresenham(x1, y1, x2, y2, color);
    rnd_bresenham(x2, y2, x0, y0, color);
}

void rnd_draw_filled_tri(int x0, int y0, int x1, int y1, int x2, int y2, unsigned char color, double light_intensity) {
    int xmin,ymin,xmax,ymax;
    int delta_w0_col,delta_w1_col,delta_w2_col;
    int delta_w0_row,delta_w1_row,delta_w2_row;
    int bias0,bias1,bias2;
    int x,y,px,py;
    int w0_row,w1_row,w2_row;

    int area = edgeFunction(x0, y0, x1, y1, x2, y2);
    if (area <= 0)
        return;

    xmin = max(0, min(min(x0, x1), x2));
    ymin = max(0, min(min(y0, y1), y2));
    xmax = min(319, max(max(x0, x1), x2));
    ymax = min(199, max(max(y0, y1), y2));

    px = xmin;
    py = ymin;

    delta_w0_col = y1 - y2;
    delta_w1_col = y2 - y0;
    delta_w2_col = y0 - y1;

    delta_w0_row = x2 - x1;
    delta_w1_row = x0 - x2;
    delta_w2_row = x1 - x0;

    bias0 = isTopLeft(x1, y1, x2, y2) ? 0 : -1;
    bias1 = isTopLeft(x2, y2, x0, y0) ? 0 : -1;
    bias2 = isTopLeft(x0, y0, x1, y1) ? 0 : -1;

    w0_row = edgeFunction(x1, y1, x2, y2, px, py) + bias0;
    w1_row = edgeFunction(x2, y2, x0, y0, px, py) + bias1;
    w2_row = edgeFunction(x0, y0, x1, y1, px, py) + bias2;

    for (y = ymin; y <= ymax; ++y) {
        int w0 = w0_row;
        int w1 = w1_row;
        int w2 = w2_row;
        
        for (x = xmin; x <= xmax; ++x) {
            if ((w0 | w1 | w2 ) >= 0) {
                _vga_put_pixel(x, y, dithering(x, y, color, light_intensity));
            }

            w0 += delta_w0_col;
            w1 += delta_w1_col;
            w2 += delta_w2_col;
        }

        w0_row += delta_w0_row;
        w1_row += delta_w1_row;
        w2_row += delta_w2_row;
    }
 }