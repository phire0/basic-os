; boot.asm
; Basic Operating System, Bootloader

[org 0x7C00]                                    ; tell the assember our bootloader offset

KERNEL_OFFSET equ 0x1000

mov [BOOT_DRIVE], dl
mov bp, 0x9000                                  ; move stack away from our bootloader, don't want to overwrite
mov sp, bp                                      ; point sp to bp

mov bx, STR_BOOTLOADER_INIT                     ; load string into BX
call rm_print                                   ; call print function
call rm_print_nl                                ; call newline print function

call kernel_init                                ; initialise kernel
call switch_to_protected_mode                   ; switch to 32-bit protected mode
jmp $                                           ; infinite loop, halt...

%include "boot/print.asm"
%include "boot/disk.asm"
%include "boot/32-bit/pmode_gdt.asm"
%include "boot/32-bit/pmode_init.asm"
%include "boot/32-bit/pmode_print.asm"

[bits 16]
kernel_init:
        mov bx, KERNEL_OFFSET                   ; Read from disk, store in 0x1000
        mov dh, 16                              ; Plenty of space for our kernel
        mov dl, [BOOT_DRIVE]
        call disk_load                          ; Load from disk
        ret                                     ; Return to caller

[bits 32]
begin_protected_mode:                           ; 32-Bit Protected Mode Entry Point
        mov ebx, STR_PROT_MODE                  ; load protected mode string into EBX
        call pm_print                           ; call print function
        call KERNEL_OFFSET                      ; give control to the kernel
        jmp $                                   ; infinite loop in case the kernel ever returns control to bootloader

BOOT_DRIVE db 0
STR_BOOTLOADER_INIT db "Loaded 16-Bit Real Mode.", 0
STR_PROT_MODE db "Loaded 32-Bit Protected Mode.", 0

times 510 - ($ - $$) db 0                       ; Fill bootsector
dw 0xAA55                                       ; Bootsector indicator