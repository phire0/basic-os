/**
 * kernel.c
 * Basic Operating System, Primary Kernel Functions
 */

/**
 * KERNEL ENTRY POINT
 */
void kernel_entry()
{
    volatile unsigned char *vga_base_address = (unsigned char*) 0xB8000;
    *vga_base_address = 'X';
}