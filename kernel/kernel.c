/**
 * kernel.c
 * Basic Operating System, Primary Kernel Functions
 */

#include "../stdlib/include/stdcolour.h"
#include "../stdlib/include/stdint.h"
#include "../stdlib/include/stdio.h"
#include "../stdlib/include/stdutils.h"

#include "../drivers/include/ports.h"
#include "../drivers/include/clock.h"

void print_test(void);


/**
 * KERNEL ENTRY POINT
 */
void kernel_entry(void)
{
    clear_screen();

    uint8_t hour = clock_r(CMOS_CLOCK_HOURS);
    uint8_t minutes = clock_r(CMOS_CLOCK_MINUTES);
    uint8_t seconds = clock_r(CMOS_CLOCK_SECONDS);

    char strBuf[4];
    kprint("The time is: ");
    kprint(int_to_char(hour, strBuf));
    kprint(":");
    kprint(int_to_char(minutes, strBuf));
    kprint(":");
    kprint(int_to_char(seconds, strBuf));
}

void print_test(void)
{
    clear_screen();

    kprint_l("Welcome to the kernel.", 29, 3);

    // Top Left Colour Sample
    kprint_la("  ", 0, 0, 0x00);
    kprint_la("  ", 2, 0, 0x10);
    kprint_la("  ", 4, 0, 0x20);
    kprint_la("  ", 6, 0, 0x30);
    kprint_la("  ", 0, 1, 0x40);
    kprint_la("  ", 2, 1, 0x50);
    kprint_la("  ", 4, 1, 0x60);
    kprint_la("  ", 6, 1, 0x70);
    kprint_la("  ", 0, 2, 0x80);
    kprint_la("  ", 2, 2, 0x90);
    kprint_la("  ", 4, 2, 0xA0);
    kprint_la("  ", 6, 2, 0xB0);
    kprint_la("  ", 0, 3, 0xC0);
    kprint_la("  ", 2, 3, 0xD0);
    kprint_la("  ", 4, 3, 0xE0);
    kprint_la("  ", 6, 3, 0xF0);

    // Top Right Alphabet Sample
    kprint_la("ABCDEFGH", 72, 0, 0x0F);
    kprint_la("IJKLMNOP", 72, 1, 0x0F);
    kprint_la("QRSTUVWX", 72, 2, 0x0F);
    kprint_la("YZabcdef", 72, 3, 0x0F);
    kprint_la("ghijklmn", 72, 4, 0x0F);
    kprint_la("opqrstuv", 72, 5, 0x0F);
    kprint_la("wxyz0123", 72, 6, 0x0F);
    kprint_la("456789", 74, 7, 0x0F);

    // Pretty hello world message
    kprint_la(" Hello, World! :) ", 31, 9, pre_kprint_attr(COLOUR_LIGHT_RED, COLOUR_BLACK));
    kprint_la(" Hello, World! :) ", 31, 10, pre_kprint_attr(COLOUR_YELLOW, COLOUR_BLACK));
    kprint_la(" Hello, World! :) ", 31, 11, pre_kprint_attr(COLOUR_LIGHT_YELLOW, COLOUR_BLACK));
    kprint_la(" Hello, World! :) ", 31, 12, pre_kprint_attr(COLOUR_LIGHT_GREEN, COLOUR_BLACK));
    kprint_la(" Hello, World! :) ", 31, 13, pre_kprint_attr(COLOUR_LIGHT_AQUA, COLOUR_BLACK));
    kprint_la(" Hello, World! :) ", 31, 14, pre_kprint_attr(COLOUR_LIGHT_BLUE, COLOUR_BLACK));
    kprint_la(" Hello, World! :) ", 31, 15, pre_kprint_attr(COLOUR_LIGHT_PURPLE, COLOUR_BLACK));
}