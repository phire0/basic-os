/**
 * stdutils.h
 * Basic Operating System, Standard Utilities
 */

#include "include/stdutils.h"

void reverse(char *str, int length);

char* int_to_char(int number, char *strBuf)
{
    return int_to_char_b(number, strBuf, 10);
}

char* int_to_char_b(int number, char *strBuf, int base)
{
    int i = 0;
    int isNegative = 0;

    // Handle 0 to avoid empty string
    if (number == 0)
    {
        strBuf[i] = '0';
        strBuf[++i] = '\0';
        return strBuf;
    }

    // Only process negative numbers for base 10
    if (number < 0 && base == 10)
    {
        isNegative = 1;
        number = -number;
    }

    // Process each digit
    while (number != 0)
    {
        int remainder = number % base;
        strBuf[i++] = (remainder > 9) ? (remainder - 10) + 'a' : remainder + '0';
        number /= base;
    }

    // Append sign if negative
    if (isNegative)
    {
        strBuf[i++] = '-';
    }

    // Add null terminator
    strBuf[i] = '\0';

    reverse(strBuf, i);

    return strBuf;
}

void reverse(char *str, int length)
{
    int start = 0;
    int end = length - 1;

    while (start < end)
    {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}