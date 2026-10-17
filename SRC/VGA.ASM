.model small
.data?
offscreen dw 4 dup (?)
vram dw 4 dup (?)
.data
.code
extrn _farmalloc:near
extrn _farfree:near
public __vgaInit
public __vgaExit
public __vgaClearOffscreen
public __vgaPutPixel
public __vgaBlit
; --------------------------------------------------------------------
; void _Cdecl __vgaInit(void)                                        ;
; --------------------------------------------------------------------
__vgaInit proc
    mov	word ptr vram + 2, 0A000h
	mov	word ptr vram, 0
    xor	ax, ax
	mov	dx, 64000
	push ax
	push dx
	call _farmalloc
	pop	cx
	pop	cx
	mov	word ptr offscreen + 2, dx
	mov	word ptr offscreen, ax
	or ax, word ptr offscreen + 2
	je error
    
    push di
    cld
    les di, dword ptr offscreen
    mov ax, 0
    mov cx, 32000
    rep stosw
    pop di

    mov	ax, 19
	push ax
	call __initMode
    pop cx
error:
    ret
__vgaInit endp
; --------------------------------------------------------------------
; void _Cdecl __vgaExit(void)                                        ;
; --------------------------------------------------------------------
__vgaExit proc
    push word ptr offscreen + 2
	push word ptr offscreen
	call _farfree
	pop	cx
	pop	cx

	mov	ax, 3
	push ax
	call __initMode
	pop	cx
    ret
__vgaExit endp
; --------------------------------------------------------------------
; void _Cdecl __vgaClearOffscreen(unsigned char color)               ;
; --------------------------------------------------------------------
__vgaClearOffscreen proc
    push bp
	mov	bp, sp
	sub	sp, 2

    ; int fill = (color << 8) | color;	
	mov	al, byte ptr [bp + 4]
	cbw	
	mov	cl, 8
	shl	ax, cl
	push ax
	mov	al, byte ptr [bp + 4]
	cbw	
	pop	dx
	or dx, ax
	mov	word ptr [bp - 2], dx

    push di
    cld
    les di, dword ptr offscreen
    mov ax, word ptr [bp - 2]
    mov cx, 32000
    rep stosw

    pop di

	mov	sp, bp
	pop	bp
    ret
__vgaClearOffscreen endp
; --------------------------------------------------------------------
; void _Cdecl __vgaPutPixel(int x, int y, char color)                ;
; --------------------------------------------------------------------
__vgaPutPixel proc
    push bp
	mov	bp, sp
	push si
	mov	si, word ptr [bp + 6] ; si = y
   
    ; offscreen[(y << 8) + (y << 6) + x] = color;	
	mov	bx, si
	mov	cl, 8
	shl	bx, cl
	mov	ax, si
	mov	cl, 6
	shl	ax, cl
	add	bx, ax
	add	bx, word ptr [bp + 4] ; bx += x

    push di
    les di, dword ptr offscreen
	add bx, di
	mov	al, byte ptr [bp + 8] ; al = color
	mov	byte ptr es:[bx], al
    pop di
 	
	pop	si
	pop	bp
    ret
__vgaPutPixel endp

; --------------------------------------------------------------------
; void _Cdecl __initMode(int mode)                                   ;
; --------------------------------------------------------------------
__initMode proc
    push bp
    mov bp, sp

    xor ah, ah    
    mov ax, [bp + 4]
    int 10h
    
    pop bp
    ret
__initMode endp

; --------------------------------------------------------------------------
; void _Cdecl _waitvretrace(void)                                          ; 
; --------------------------------------------------------------------------
__waitvretrace proc
    cli
l1: 
    mov dx, 03dah 
    in al, dx      
    test al, 8h   
    jnz l1
    
l2:
    mov dx, 03dah
    in al, dx
    test al, 8h
    jz l2          
    sti
    ret
__waitvretrace endp

; --------------------------------------------------------------------------
; void _Cdecl _blit(void)                                                  ; 
; --------------------------------------------------------------------------
__vgaBlit proc
    call __waitvretrace
    push ds                       
    push si                       
    push di                       

    cld
    les di, dword ptr vram
    lds si, dword ptr offscreen
    mov cx, 32000
    rep movsw
    
    pop di                       
    pop si                       
    pop ds
    ret
__vgaBlit endp
end