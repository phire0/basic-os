; disk.asm
; Basic Operating System, Bootloader Disk Management

; We will load 'DH' sectors from drive 'DL' into ES:BX
; [ES:BX] is a pointer to the buffer where data will be stored
; The caller sets this up for us and this is the standard location for int 0x13

disk_load:
        pusha                                   ; push all general purpose registers onto stack
        push dx                                 ; put our input params onto the stack for later use

        mov ah, 0x02                            ; tell the BIOS we want to read

        mov al, dh                              ; al - number of sectors to read (0x01 ... 0x80)
        mov cl, 0x02                            ; cl - sector (0x01 ... 0x11)
                                                ; 0x01 is our boot sector, 0x02 is first 'available' sector

        mov ch, 0x00                            ; ch - cylinder (0x0 ... 0x3FF, upper two bits in CL)
                                                ; dl - drive number, caller sets it as param and gets from BIOS
                                                ; (0 = floppy, 1 = floppy1, 0x80 = HDD, 0x81 = HDD2)
        
        mov dh, 0x00                            ; dh - head number (0x0 ... 0xF)

        int 0x13                                ; BIOS interrupt
        jc disk_error                           ; Jump if error detected, stored in carry bit

        pop dx
        cmp al, dh                              ; BIOS sets AL to number of sectors read
        jne sector_error                        ; if incorrect number of sectors read, error

        mov bx, STR_DISK_SUCCESS                ; Display a notice if we successfully read disk
        call rm_print
        call rm_print_nl

        jmp boot_disk_done                      ; done

disk_error:
        mov bx, STR_DISK_ERROR                  ; load disk error message into bx
        call rm_print                           ; call print
        call rm_print_nl
        mov bx, STR_ERROR_CODE_PREFIX
        call rm_print
        mov dh, ah                              ; load error code into dh
        call rm_print_hex                       ; print error code
        jmp boot_disk_done                      ; done

sector_error:
        mov bx, STR_SECTOR_ERROR                ; load sector error message into bx
        call rm_print                           ; call print
        call rm_print_nl
        jmp boot_disk_done                      ; done

boot_disk_done:
        popa
        ret

STR_DISK_ERROR: db "Error: Failed to read disk.", 0
STR_ERROR_CODE_PREFIX: db "Error Code: ", 0
STR_SECTOR_ERROR: db "Error: Incorrect number of sectors read.", 0
STR_DISK_SUCCESS: db "Disk Read Successfully!", 0