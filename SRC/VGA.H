#ifndef VGA_H
#define VGA_H

#include <_defs.h>

void _Cdecl _vgaInit(void);

void _Cdecl _vgaExit(void);
  
void _Cdecl _vgaPutPixel(int x, int y, unsigned char color);

void _Cdecl _vgaClearOffscreen(unsigned char color);

void _Cdecl _vgaBlit(void);

#endif