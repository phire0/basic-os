/**
 * stdio.c
 * Basic Operating System, Standard Input/Output
 */

#include "include/stdio.h"
#include "include/stdcolour.h"

#include "../drivers/include/screen.h"

/**
 * Clear all contents from the screen
 */
void clear_screen(void)
{
    unsigned char *vgaBaseAddy = (unsigned char*) VIDEO_BASE_ADDRESS;
    int screenSize = MAX_COLS * MAX_ROWS;

    for (int i = 0; i < screenSize; i++)
    {
        vgaBaseAddy[i * 2] = ' ';
        vgaBaseAddy[i * 2 + 1] = pre_kprint_attr(COLOUR_BLACK, COLOUR_BRIGHT_WHITE);
    }

    set_cursor_offset(get_offset(0, 0));
}

/**
 * Print a given message
 * @param str The string to print
 */
void kprint(char *str)
{
    kprint_la(str, -1, -1, 0);
}

void kprint_f(char *str, ...)
{
    kprint(str);
}

/**
 * Print a given message at the specified location
 * @param str The string to print
 * @param column Column output location
 * @param row Row output location
 */
void kprint_l(char *str, int column, int row)
{
    kprint_la(str, column, row, 0);
}

/**
 * Print a given message at the specified location with attributes
 * @param str The string to print
 * @param column Column output location
 * @param row Row output location
 */
void kprint_la(char *str, int column, int row, char attr)
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
    while (str[i] != '\0')
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
char pre_kprint_attr(char background, char foreground)
{
    return (background << 4) | foreground;
}