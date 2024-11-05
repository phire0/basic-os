; print.asm
; Basic Operating System, 16-Bit Real Mode Printing

rm_print:
        pusha                                   ; push all general purpose registers onto stack
        jmp rm_print_start                      ; start printing functionality
        jmp rm_print_done                       ; finished

rm_print_nl:
        pusha                                   ; push all general purpose registers onto stack
        jmp rm_print_newline_start              ; start newline printing functionality
        jmp rm_print_done                       ; finished

rm_print_hex:
        pusha                                   ; push all general purpose registers onto stack
        mov cx, 0                               ; index variable for hex loop
        jmp rm_print_hex_start                  ; start hex printing functionality
        jmp rm_print_done                       ; finished

rm_print_start:
        mov al, [bx]                            ; 'bx' is agreed base address for input string
        cmp al, 0                               ; check for string terminator
        je rm_print_done                        ; found 0? done!

        mov ah, 0x0E                            ; tty mode
        int 0x10                                ; call BIOS interrupt, print character

        add bx, 1                               ; increment loop counter
        jmp rm_print_start                      ; iterate

rm_print_newline_start:
        mov ah, 0x0E                            ; tty mode
        mov al, 0x0A                            ; newline character
        int 0x10                                ; call BIOS interrupt, print character
        mov al, 0x0D                            ; carriage return
        int 0x10                                ; call BIOS interrupt, print character
        jmp rm_print_done                       ; done

rm_print_hex_start:
        cmp cx, 4                               ; loop four times
        je rm_print_hex_end                     ; looped four times? end

        mov ax, dx                              ; work in AX register
        and ax, 0x000F                          ; 0x1234 -> 0x0004, mask first three to 0
        add al, 0x30                            ; add 0x30 to convert to ASCII
        cmp al, 0x39                            ; if > 9 add 8 to represent 'A' to 'F'
        jle rm_print_hex_step_two
        add al, 7

rm_print_hex_step_two:
        mov bx, HEX_OUT + 5                     ; base + length
        sub bx, cx                              ; loop index variable defined in print_hex
        mov [bx], al                            ; copy ASCII char on AL to value pointed to bt BC
        ror dx, 4                               ; rotate DX

        add cx, 1                               ; increment loop
        jmp rm_print_hex_start                  ; iterate

rm_print_hex_end:
        mov bx, HEX_OUT                         ; put print param into bx
        call rm_print                              ; print output
        jmp rm_print_done                       ; finished

rm_print_done:
        popa                                    ; return previous contents to their registers
        ret                                     ; return to caller

HEX_OUT: db '0x0000', 0                         ; reserve memory for hex string