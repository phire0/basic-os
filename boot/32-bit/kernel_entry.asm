; kernel_entry.asm
; Basic Operating System, Load C Kernel Code

[bits 32]                                       ; Runs in 32-Bit Protected Mode
[extern kernel_entry]                           ; Define kernel entry point
call kernel_entry                               ; Call kernel entry point
jmp $                                           ; Infinite loop