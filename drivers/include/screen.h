/**
 * screen.h
 * Basic Operating System, Kernel Screen Management
 */

#ifndef _DRIVER_SCREEN_H
#define _DRIVER_SCREEN_H

// Video Memory Management Definitions
#define VIDEO_BASE_ADDRESS 0xB8000
#define MAX_ROWS 25
#define MAX_COLS 80

// Screen IO Port Address Registers
#define VGA_SCREEN_CTRL_REGISTER 0x3D4
#define VGA_SCREEN_DATA_REGISTER 0x3D5

// VGA Cursor Position Bytes
#define VGA_CURSOR_POS_HIGH_BYTE 14
#define VGA_CURSOR_POS_LOW_BYTE 15

/**
 * Helps to print characters, does most of the barebones work
 * like directly accessing video memory.
 * 
 * If column/row are negative, we will print to current cursor location
 * If attr is 0 we will use WHITE_ON_BLACK by default
 * 
 * Sets cursor to returned offset
 * 
 * @param c the character to print
 * @param column column output location
 * @param row row output location
 * @param attr colour attributes, default 0 as WHITE_ON_BLACK
 * @return the offset of the next character
 */
int print_char(char c, int column, int row, char attr);

/**
 * Set the cursor offset
 * @param offset new cursor offset value
 */
void set_cursor_offset(int offset);

/**
 * Get the cursor offset
 * @return The cursor offset
 */
int get_cursor_offset(void);

/**
 * Get offset
 * @param column The column position
 * @param row The row position
 * @return the offset
 */
int get_offset(int column, int row);

/**
 * Get the offset for a row
 * @param offset The offset
 * @return Row offset
 */
int get_offset_row(int offset);

/**
 * Get the offset for a column
 * @param offset The offset
 * @return Column offset
 */
int get_offset_column(int offset);

#endif