#include "mem.h"

void far* _Cdecl _memsetw(void far* dest, int val, unsigned count) {
    void far* result = dest;

    asm {
        push es

        les di, dest
        mov ax, val
        mov cx, count
        rep stosw

        pop es
    }

    return result;
}

void far* _Cdecl _memcpyw(void far* dest, void far* src, unsigned count) {
    void far* result = dest;

    asm {
        push ds
        push es

        les di, dest
        lds si, src
        mov cx, count
        rep movsw

        pop es
        pop ds
    }

    return result;
}