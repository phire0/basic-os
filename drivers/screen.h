// Video Memory Management Definitions
#define VIDEO_BASE_ADDRESS 0xB8000
#define MAX_ROWS 25
#define MAX_COLS 80

// Colour Options
#define COLOUR_BLACK 0x0
#define COLOUR_BLUE 0x1
#define COLOUR_GREEN 0x2
#define COLOUR_AQUA 0x3
#define COLOUR_RED 0x4
#define COLOUR_PURPLE 0x5
#define COLOUR_YELLOW 0x6
#define COLOUR_WHITE 0x7
#define COLOUR_GREY 0x8
#define COLOUR_LIGHT_BLUE 0x9
#define COLOUR_LIGHT_GREEN 0xA
#define COLOUR_LIGHT_AQUA 0xB
#define COLOUR_LIGHT_RED 0xC
#define COLOUR_LIGHT_PURPLE 0xD
#define COLOUR_LIGHT_YELLOW 0xE
#define COLOUR_BRIGHT_WHITE 0xF

// Screen IO Port Address Registers
#define VGA_SCREEN_CTRL_REGISTER 0x3D4
#define VGA_SCREEN_DATA_REGISTER 0x3D5

// VGA Cursor Position Bytes
#define VGA_CURSOR_POS_HIGH_BYTE 14
#define VGA_CURSOR_POS_LOW_BYTE 15

// Public kernel screen API

/**
 * Clear all contents from the screen
 */
void clear_screen();

/**
 * Print a given message
 * @param str The string to print
 */
void kprint(char *str);

/**
 * Print a given message at the specified location
 * @param str The string to print
 * @param column Column output location
 * @param row Row output location
 */
void kprint_at(char *str, int column, int row, char attr);

/**
 * Quickly convert specified background/foreground colour values
 * into valid attr value for krpint_at
 * @param background the background colour, hex 0 to F or use colour defined in screen.h
 * @param foreground the foreground colour, hex 0 to F or use colour defined in screen.h
 * @return The proper hex value with the chosen attributes
 */
char kprint_attr(char background, char foreground);