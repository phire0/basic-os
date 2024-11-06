/**
 * ports.c
 * Basic Operating System, Port In/Out
 */

/**
 * Read a byte from the specified port
 */
unsigned char read_byte_from_port(unsigned short port) {
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
 * Write a byte to the specified port
 */
void write_byte_to_port(unsigned short port, unsigned char data) {
    /* 
     * Notice how here both registers are mapped to C variables and
     * nothing is returned, thus, no equals '=' in the asm syntax 
     * However we see a comma since there are two variables in the input area
     * and none in the 'return' area
     */
    __asm__("out %%al, %%dx" : : "a" (data), "d" (port));
}