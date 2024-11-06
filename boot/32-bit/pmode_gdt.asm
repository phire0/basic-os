; pmode_gdt.asm
; Basic Operating System, Global Descriptor Table (GDT)

gdt_start:
        dd 0x0                                  ; The GDT begins with a NULL 8 bytes
        dd 0x0                                  ; ^
    
gdt_code:
        ; GDT for code segment
        ; Base = 0x00000000, length = 0xFFFFF
        dw 0xFFFF                               ; segment length, bits 0-15
        dw 0x0                                  ; segment base, bits 0-15
        db 0x0                                  ; segment base, bits 16-23
        db 10011010b                            ; flags (8 bits)
        db 11001111b                            ; flags (4 byts) + segment length. bits 16-19
        db 0x0                                  ; segment base, bits 24-31

gdt_data:
        ; GDT for data segment
        ; Base = 0x00000000, length = 0xFFFFF
        ; Some flags different
        dw 0xFFFF                               ; segment length, bits 0-15
        dw 0x0                                  ; segment base, bits 0-15
        db 0x0                                  ; segment base, bits 16-23
        db 10010010b                            ; flags (8 bits)
        db 11001111b                            ; flags (4 byts) + segment length. bits 16-19
        db 0x0                                  ; segment base, bits 24-31

gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1                  ; size (16 bit), always one less than its true size
    dd gdt_start                                ; address (32 bit)

; CONSTANTS
CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start