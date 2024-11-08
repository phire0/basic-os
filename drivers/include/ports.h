/**
 * ports.h
 * Basic Operating System, Port In/Out
 */

#ifndef _DRIVER_PORTS_H
#define _DRIVER_PORTS_H

#include "../../stdlib/include/stdint.h"

/**
 * Read a byte of data from the specified port
 * @param port The port to read from
 * @return Returns the data stored in the specified port
 */
uint8_t read_byte_from_port(uint16_t port);

/**
 * Write a byte of data to the specified port
 * @param port The port to write to
 * @param data The data to write to the given port
 */
void write_byte_to_port(uint16_t port, uint8_t data);

#endif