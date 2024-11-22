/**
 * stdstring.c
 * Basic Operating System, String Utilities
 */

#include "include/stdstring.h"

int strlen(const char* str)
{
    int length = 0;
    int counter = 0;
    
    while (str[counter++] != '\0')
    {
        ++length;
    }

    return length;
}

int strcmp(const char* str_a, const char* str_b)
{
    return 0;
}