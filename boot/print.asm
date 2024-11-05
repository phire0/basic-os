; print.asm
; Basic Operating System, 16-Bit Real Mode Printing
                                                ; alignment
rm_print:
        pusha                                   ; push all general purpose registers onto stack
        jmp rm_print_start                      ; start printing functionality
        jmp rm_print_done                       ; finished

rm_print_start:
        mov al, [bx]                            ; 'bx' is agreed base address for input string
        cmp al, 0                               ; check for string terminator
        je rm_print_done                        ; found 0? done!

        mov ah, 0x0E                            ; tty mode
        int 0x10                                ; call BIOS interrupt, print character

        add bx, 1                               ; increment loop counter
        jmp rm_print_start                      ; iterate

rm_print_done:
    popa                                        ; return previous contents to their registers
    ret                                         ; return to caller