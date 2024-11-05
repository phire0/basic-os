; boot.asm
; Basic Operating System, Bootloader

[org 0x7C00]                                    ; tell the assember our bootloader offset

mov bp, 0x9000                                  ; move stack away from our bootloader, don't want to overwrite
mov sp, bp                                      ; point sp to bp

mov bx, STR_BOOTLOADER_INIT                     ; load string into bx
call rm_print                                   ; call print function
call rm_print_nl                                ; call newline print function
mov dx, 0xABCD                                  ; load 0xABCD into DX
call rm_print_hex                               ; call print hex function


jmp $                                           ; infinite loop, halt...

%include "boot/print.asm"

STR_BOOTLOADER_INIT db "Loaded 16-Bit Real Mode.", 0

times 510 - ($ - $$) db 0                       ; Fill bootsector
dw 0xAA55                                       ; Bootsector indicator