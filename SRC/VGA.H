#ifndef VGA_H
#define VGA_H

void vgaInit(void);

void vgaExit(void);
  
void vgaPutPixel(int x, int y, char color);

void vgaClearOffscreen(char color);

void vgaUpdateVram(void);

#endif