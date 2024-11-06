; pmode_print.asm
; Basic Operating System, 32-Bit Protected Mode Printing Functionality

; 32-Bit Protected Mode allows us to utilise 32-bit registers, and use cool things like
; memory addressing, protected memory, virtual memory, and much more.
; Unfortunately though, we lose access to things like BIOS interrupts which we were previously
; using to print messages. Thus, we will need a way to print whilst in 32-bit protected mode.

; We will directly manipulate VGA memory, which begins at 0xB8000
; Formula for accessing specific char on 80x25 grid: 0xB8000 + 2 * (row * 80 + col)

[bits 32]                                       ; using 32-bit protected mode

; CONSTANTS
VIDEO_MEMORY equ 0xB8000                        ; VGA base address
WHITE_ON_BLACK equ 0x0F                         ; colour byte for each character

pm_print:
    pusha                                       ; load general purpose registers onto stack
    mov edx, VIDEO_MEMORY                       ; move VGA base address into EDX

pm_print_loop:
    mov al, [ebx]                               ; EBX has address for our character
    mov ah, WHITE_ON_BLACK

    cmp al, 0                                   ; check for string terminator
    je pm_print_done                            ; found it? finished

    mov [edx], ax                               ; store character + attribute in video memory
    add ebx, 1                                  ; next character
    add edx, 2                                  ; next video memory position

    jmp pm_print_loop

pm_print_done:
    popa                                        ; return stack to registers
    ret                                         ; return to caller