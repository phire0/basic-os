/**
 * screen.c
 * Basic Operating System, Kernel Screen Management
 */

#include "screen.h"
#include "ports.h"

// Declare private helper functions
void set_cursor_offset(int offset);
int get_cursor_offset();
int get_offset(int column, int row);
int get_offset_row(int offset);
int get_offset_column(int offset);
int print_char(char c, int column, int row, char attr);

/****************************************************
 * Public Kernel Screen API Functions
 ****************************************************/

/**
 * Clear all contents from the screen
 */
void clear_screen()
{
    unsigned char *vgaBaseAddy = (unsigned char*) VIDEO_BASE_ADDRESS;
    int screenSize = MAX_COLS * MAX_ROWS;

    for (int i = 0; i < screenSize; i++)
    {
        vgaBaseAddy[i * 2] = ' ';
        vgaBaseAddy[i * 2 + 1] = kprint_attr(COLOUR_BLACK, COLOUR_BRIGHT_WHITE);
    }

    set_cursor_offset(get_offset(0, 0));
}

/**
 * Print a given message
 * @param str The string to print
 */
void kprint(char *str)
{
    kprint_at(str, -1, -1, 0);
}

/**
 * Print a given message at the specified location
 * @param str The string to print
 * @param column Column output location
 * @param row Row output location
 */
void kprint_at(char *str, int column, int row, char attr)
{
    int offset;

    // Get cursor offset
    if (column >= 0 && row >= 0)
    {
        offset = get_offset(column, row);
    }
    else
    {
        // column/row param is negative
        // so get offset and figure out column/row
        offset = get_cursor_offset();

        column = get_offset_column(offset);
        row = get_offset_row(offset);
    }

    // Iterate through string and print it
    int i = 0;
    while (str[i] != 0)
    {
        offset = print_char(str[i++], column, row, attr);

        // Update column/row for next iteration
        column = get_offset_column(offset);
        row = get_offset_row(offset);
    }
}

/**
 * Quickly convert specified background/foreground colour values
 * into valid attr value for krpint_at
 * @param background the background colour, hex 0 to F or use colour defined in screen.h
 * @param foreground the foreground colour, hex 0 to F or use colour defined in screen.h
 * @return The proper hex value with the chosen attributes
 */
char kprint_attr(char background, char foreground)
{
    return (background << 4) | foreground;
}

/****************************************************
 * Private Helper Functions
 ****************************************************/

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
int print_char(char c, int column, int row, char attr)
{
    unsigned char *vgaBaseAddy = (unsigned char*) VIDEO_BASE_ADDRESS;

    // TODO: Implement additional options.
    if (!attr || attr == 0)
    {
        attr = kprint_attr(COLOUR_BLACK, COLOUR_BRIGHT_WHITE);
    }

    // Error Handling, print red 'E' if coordinates are incorrect.
    if (column >= MAX_COLS || row >= MAX_ROWS)
    {
        vgaBaseAddy[2 * MAX_COLS * MAX_ROWS - 2] = 'E';
        vgaBaseAddy[2 * MAX_COLS * MAX_ROWS - 2] = kprint_attr(COLOUR_BRIGHT_WHITE, COLOUR_RED);
        return get_offset(column, row);
    }

    // Process regular printing functionality
    int offset;

    // Get the proper cursor offset value
    if (column >= 0 && row >= 0)
    {
        offset = get_offset(column, row);
    }
    else
    {
        offset = get_cursor_offset();
    }

    // Newline character
    if (c == '\n')
    {
        row = get_offset_row(offset);
        offset = get_offset(0, row + 1);
    }
    // Other
    else
    {
        vgaBaseAddy[offset] = c;
        vgaBaseAddy[offset + 1] = attr;
        offset += 2;
    }

    set_cursor_offset(offset);

    return offset;
}

/**
 * Get the cursor offset
 * @returns The cursor offset
 */
int get_cursor_offset()
{
    // Store cursor position
    int cursorPosition = -1;

    // Request high byte of cursor position
    write_byte_to_port(VGA_SCREEN_CTRL_REGISTER, VGA_CURSOR_POS_HIGH_BYTE);

    // Read high byte
    cursorPosition = read_byte_from_port(VGA_SCREEN_DATA_REGISTER);

    // Shift to get high byte
    cursorPosition = cursorPosition << 8;

    // Request low byte of cursor position
    write_byte_to_port(VGA_SCREEN_CTRL_REGISTER, VGA_CURSOR_POS_LOW_BYTE);

    // Read low byte
    cursorPosition += read_byte_from_port(VGA_SCREEN_DATA_REGISTER);

    // VGA 'cells' consist of the character and its control data
    // e.g. 'white on black background', 'red text on white background', etc
    return cursorPosition * 2;
}

/**
 * Set the cursor offset
 * @param offset new cursor offset value
 */
void set_cursor_offset(int offset)
{
    int cursorPosition = offset / 2;

    write_byte_to_port(VGA_SCREEN_CTRL_REGISTER, VGA_CURSOR_POS_HIGH_BYTE);
    write_byte_to_port(VGA_SCREEN_DATA_REGISTER, (cursorPosition >> 8));
    write_byte_to_port(VGA_SCREEN_CTRL_REGISTER, VGA_CURSOR_POS_LOW_BYTE);
    write_byte_to_port(VGA_SCREEN_DATA_REGISTER, (cursorPosition & 0xFF));
}

int get_offset(int column, int row)
{
    return 2 * (row * MAX_COLS + column);
}

int get_offset_row(int offset)
{
    return offset / (2 * MAX_COLS);
}

int get_offset_column(int offset)
{
    return (offset - (get_offset_row(offset) * 2 * MAX_COLS)) / 2;
}