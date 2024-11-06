/**
 * kernel.c
 * Basic Operating System, Primary Kernel Functions
 */

#include "../drivers/screen.h"

void print_test();

/**
 * KERNEL ENTRY POINT
 */
void kernel_entry(void)
{
    print_test();
}

void print_test()
{
    clear_screen();
    kprint("Top Left Text");
    kprint_at("Top Right Text", 66, 0, 0);
    kprint_at("This contains a\nline break!", 30, 5, 0);
    kprint_at("What happens when we run out of space?", 45, 24, 0);
    kprint_at("Hello, World! :)", 30, 10, kprint_attr(COLOUR_LIGHT_RED, COLOUR_BLACK));
    kprint_at("Hello, World! :)", 30, 11, kprint_attr(COLOUR_YELLOW, COLOUR_BLACK));
    kprint_at("Hello, World! :)", 30, 12, kprint_attr(COLOUR_LIGHT_YELLOW, COLOUR_BLACK));
    kprint_at("Hello, World! :)", 30, 13, kprint_attr(COLOUR_LIGHT_GREEN, COLOUR_BLACK));
    kprint_at("Hello, World! :)", 30, 14, kprint_attr(COLOUR_LIGHT_AQUA, COLOUR_BLACK));
    kprint_at("Hello, World! :)", 30, 15, kprint_attr(COLOUR_LIGHT_BLUE, COLOUR_BLACK));
    kprint_at("Hello, World! :)", 30, 16, kprint_attr(COLOUR_LIGHT_PURPLE, COLOUR_BLACK));
}