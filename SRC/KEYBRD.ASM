.model small
.data?
old_irq	db 4 dup (?)
keys db	256 dup (?)
.data
IRQ_PORT    EQU 020h
KBC_IRQ     EQU 009h
KBC_PORT    EQU 060h
KBC_SCP     EQU 061h
KBC_BREAK   EQU 080h
SCP_KBC_DIS EQU 080h
.code
public	__kbHit
public	__kbExit
public	__kbInit

__kbc_irq_handler proc far
	push ax
	push bx
	push dx
	push ds
	push bp

    mov ax, DGROUP
	mov ds, ax
    
    mov bp, sp
	sub	sp, 2
 
	mov	byte ptr [bp - 2], 1

	cli
	in al, KBC_PORT
	mov	byte ptr [bp - 1], al	
	and	al, KBC_BREAK
	je PRESSED
  	
	mov	byte ptr [bp - 2], 0
	mov	al, byte ptr [bp - 1]	
	sub	al, KBC_BREAK
	mov	byte ptr [bp - 1], al
PRESSED:
	mov	al, byte ptr [bp - 1]
	mov	ah, 0
	mov	dl, byte ptr [bp - 2]
	mov	bx, ax
	mov	byte ptr keys[bx], dl
 
	in al, KBC_SCP	
	mov	ah, al
	or al, SCP_KBC_DIS
	out	KBC_SCP, al
	mov	al, ah
	out	KBC_SCP, al	
	mov	al, 020H
	out	IRQ_PORT, al	
	sti
    mov sp, bp
	pop bp
	pop ds
	pop dx
	pop bx
	pop ax
	iret	
__kbc_irq_handler endp

; --------------------------------------------------------------------------
; void _Cdecl _kbInit(void)                                                ; 
; --------------------------------------------------------------------------
__kbInit proc
    push bx
    push es
    ; https://wiki.osdev.org/Interrupt_Vector_Table 
    ; Calculates the offset within the interrupt vector table for IRQ 9
    mov bx, KBC_IRQ * 4                             
    xor ax, ax
    ; set up the segment register es to point to the beginning of the interrupt vector table.
    mov es, ax                                      
    cli
    ; Loads the offset of the old interrupt handler address
    mov ax, es:[bx]                                 
    mov word ptr old_irq, ax    
    ; Loads the segment of the old interrupt handler address           
    mov ax, es:[bx + 2]                             
    mov word ptr old_irq[2], ax                     
    
    ; Replaces the old interrupt handler address with the address of __kbc_irq_handler.
    mov word ptr es:[bx], offset __kbc_irq_handler  
    mov es:[bx + 2], cs                           
    sti
    pop es
    pop bx
    ret
__kbInit endp

; --------------------------------------------------------------------------
; void _Cdecl _kbExit(void)                                          ; 
; --------------------------------------------------------------------------
__kbExit proc
    push bx
    push es
    mov bx, KBC_IRQ * 4
    xor ax, ax
    mov es, ax
    cli
    mov ax, word ptr old_irq
    mov es:[bx], ax
    mov ax, word ptr old_irq[2]
    mov es:[bx + 2], ax
    sti
    pop  es
    pop  bx
    ret
__kbExit endp

; --------------------------------------------------------------------------
; void _Cdecl _kbHit(KeyCode key)                                          ; 
; --------------------------------------------------------------------------
__kbHit proc
    push bp
	mov	bp, sp
	push si
	mov	si, word ptr [bp + 4]
   
    ;if (key < 0 || key >= 256)
	or si, si
	jl ZERO
	cmp	si, 256
	jl KEYS
ZERO:
    xor	ax, ax
	jmp	FINAL
KEYS:
	mov	al, byte ptr keys[si]
	mov	ah, 0
FINAL:
    pop	si
	pop	bp
    ret
__kbHit endp
end