/**
 * screen.c
 * Basic Operating System, Kernel Screen Management
 */

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

void set_cursor_offset(int offset);
int get_cursor_offset(void);
int get_offset(int column, int row);
int get_offset_row(int offset);
int get_offset_column(int offset);
int print_char(char c, int column, int row, char attr);