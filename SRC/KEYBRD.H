#ifndef KEYBRD_H
#define KEYBRD_H

#include <_defs.h>

typedef enum {
    R_ARROW = 0x4D,
    L_ARROW = 0x4B,
    U_ARROW = 0x48,
    D_ARROW = 0x50,
    W       = 0x11,	
    A       = 0x1E,	
    S       = 0x1F,
    D       = 0x20,
    NUM_1   = 0x02,
    NUM_2   = 0x03,
    NUM_3   = 0x04,
    NUM_4   = 0x05,
    ESC     = 0x01
} KeyCode;

void _Cdecl _kb_init(void);

void _Cdecl _kb_exit(void);

int _Cdecl _kb_hit(KeyCode key);

#endif

