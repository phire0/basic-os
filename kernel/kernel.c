/**
 * kernel.c
 * Basic Operating System, Primary Kernel Functions
 */

#include "../drivers/ports.h"

/**
 * KERNEL ENTRY POINT
 */
void kernel_entry()
{
    /**
     * Screen cursor position:
     * ask VGA control register (0x3D4) for bytes
     * 14 = high byte of cursor
     * 15 = low byte of cursor
     */

    // Requesting byte 14 (high byte of cursor position)
    write_byte_to_port(0x3D4, 14);

    // Data will be stored in VGA data register 0x3D5
    int cursorPosition = read_byte_from_port(0x3D5);

    // Get the high byte
    cursorPosition = cursorPosition << 8;

    // Request byte 15 (low byte of cursor position)
    write_byte_to_port(0x3D4, 15);

    // Data will be stored in VGA data register (0x3D5)
    cursorPosition += read_byte_from_port(0x3D5);

    // VGA 'cells' considt of the character and its control data
    // e.g. 'white on black background', 'red text on white background', etc
    int vgaOffset = cursorPosition * 2;

    volatile unsigned char *vgaBaseAddress = (char*) 0xB8000;
    vgaBaseAddress[vgaOffset] = 'X';
    vgaBaseAddress[vgaOffset+1] = 0x0F;
}