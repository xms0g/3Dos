#ifndef VGA_H
#define VGA_H

#include <_defs.h>

void _Cdecl _vga_init(void);

void _Cdecl _vga_exit(void);
  
void _Cdecl _vga_put_pixel(int x, int y, unsigned char color);

void _Cdecl _vga_clr_offscreen(unsigned char color);

void _Cdecl _vga_blit(void);

#endif