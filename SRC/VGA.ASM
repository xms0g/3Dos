.model small
.data?
offscreen dw 4 dup (?)
vram dw 4 dup (?)
.data
.code
extrn _farmalloc:near
extrn _farfree:near
public __vga_init
public __vga_exit
public __vga_clr_offscreen
public __vga_put_pixel
public __vga_blit
; --------------------------------------------------------------------
; void _Cdecl __vga_init(void)                                        ;
; --------------------------------------------------------------------
__vga_init proc
    mov	word ptr vram[2], 0A000h
	mov	word ptr vram, 0
    xor	ax, ax
	mov	dx, 64000
	push ax
	push dx
	call _farmalloc
	add sp, 4
	mov	word ptr offscreen[2], dx
	mov	word ptr offscreen, ax
	or ax, word ptr offscreen[2]
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
	call __init_mode
    add sp, 2
error:
    ret
__vga_init endp
; --------------------------------------------------------------------
; void _Cdecl __vga_exit(void)                                        ;
; --------------------------------------------------------------------
__vga_exit proc
    push word ptr offscreen[2]
	push word ptr offscreen
	call _farfree
	add sp, 4

	mov	ax, 3
	push ax
	call __init_mode
	add sp, 2
    ret
__vga_exit endp
; --------------------------------------------------------------------
; void _Cdecl __vga_clr_offscreen(unsigned char color)               ;
; --------------------------------------------------------------------
__vga_clr_offscreen proc
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
__vga_clr_offscreen endp
; --------------------------------------------------------------------
; void _Cdecl __vga_put_pixel(int x, int y, char color)                ;
; --------------------------------------------------------------------
__vga_put_pixel proc
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
__vga_put_pixel endp

; --------------------------------------------------------------------
; void _Cdecl __init_mode(int mode)                                   ;
; --------------------------------------------------------------------
__init_mode proc
    push bp
    mov bp, sp

    xor ah, ah    
    mov ax, [bp + 4]
    int 10h
    
    pop bp
    ret
__init_mode endp

; --------------------------------------------------------------------------
; void _Cdecl _waitvretrace(void)                                          ; 
; --------------------------------------------------------------------------
__wait_vretrace proc
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
__wait_vretrace endp

; --------------------------------------------------------------------------
; void _Cdecl _blit(void)                                                  ; 
; --------------------------------------------------------------------------
__vga_blit proc
    call __wait_vretrace
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
__vga_blit endp
end