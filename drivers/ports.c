/**
 * ports.c
 * Basic Operating System, Port In/Out
 */

#include "../stdlib/include/stdint.h"

/**
 * Read a byte of data from the specified port
 * @param port The port to read from
 * @return Returns the data stored in the specified port
 */
uint8_t read_byte_from_port(uint16_t port) {
    // Will store the value from port
    unsigned char result;

    /* 
     * Inline assembler syntax
     * !! Notice how the source and destination registers are switched from NASM !!
     *
     * '"=a" (result)'; set '=' the C variable '(result)' to the value of register EAX
     * '"d" (port)': map the C variable '(port)' into EDX register
     */
    __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
    
    // Return port value
    return result;
}

/**
 * Write a byte of data to the specified port
 * @param port The port to write to
 * @param data The data to write to the given port
 */
void write_byte_to_port(uint16_t port, uint8_t data) {
    /* 
     * Notice how here both registers are mapped to C variables and
     * nothing is returned, thus, no equals '=' in the asm syntax 
     * However we see a comma since there are two variables in the input area
     * and none in the 'return' area
     */
    __asm__("out %%al, %%dx" : : "a" (data), "d" (port));
}