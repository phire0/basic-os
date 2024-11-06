/**
 * Read a byte of data from the specified port
 * @param port The port to read from
 * @return Returns the data stored in the specified port
 */
unsigned char read_byte_from_port(unsigned short port);

/**
 * Write a byte of data to the specified port
 * @param port The port to write to
 * @param data The data to write to the given port
 */
void write_byte_to_port(unsigned short port, unsigned char data);