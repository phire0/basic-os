; pmode_init.asm
; Basic Operating System, Initialise 32-Bit Protected Mode

[bits 16]
switch_to_protected_mode:
        cli                                     ; Disable interrupts
        lgdt [gdt_descriptor]                   ; Load GDT Descriptor

        mov eax, cr0                            ; Move contents of control register to EAX
        or eax, 0x1                             ; Set Protection Enable (PE) bit to 1
        mov cr0, eax                            ; Move EAX back to control register, tell CPU to enable protected mode

        jmp CODE_SEG:initialise_protected_mode  ; Jump to protected mode initialisation in 32 bit mode

[bits 32]
initialise_protected_mode:
        mov ax, DATA_SEG                        ; Update registers
        mov ds, ax
        mov ss, ax
        mov es, ax
        mov fs, ax
        mov gs, ax

        mov ebp, 0x90000                        ; set stack to top of free space
        mov esp, ebp                            ; point esp to ebp

        call begin_protected_mode               ; protected mode entry point in boot.asm