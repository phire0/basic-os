; boot.asm
; Basic Operating System, Bootloader

[org 0x7C00]                                    ; tell the assember our bootloader offset

mov bp, 0x9000                                  ; move stack away from our bootloader, don't want to overwrite
mov sp, bp                                      ; point sp to bp

mov bx, STR_BOOTLOADER_INIT                     ; load string into bx
call rm_print                                   ; call print function
call rm_print_nl                                ; call newline print function

call switch_to_protected_mode                   ; switch to 32-bit protected mode
jmp $                                           ; infinite loop, halt...

%include "boot/print.asm"
%include "boot/32-bit/pmode_gdt.asm"
%include "boot/32-bit/pmode_init.asm"
%include "boot/32-bit/pmode_print.asm"

[bits 32]
begin_protected_mode:
        mov ebx, STR_PROT_MODE
        call pm_print
        jmp $

STR_BOOTLOADER_INIT db "Loaded 16-Bit Real Mode.", 0
STR_PROT_MODE db "Loaded 32-Bit Protected Mode.", 0

times 510 - ($ - $$) db 0                       ; Fill bootsector
dw 0xAA55                                       ; Bootsector indicator