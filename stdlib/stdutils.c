/**
 * stdutils.c
 * Basic Operating System, Standard Utilities
 */

#include "include/stdutils.h"
#include "include/stdbool.h"

// Private internal functions
void reverse(char *str, int length);

/**
 * Convert an integer to a char*
 * @param number The integer to convert
 * @param strBuf The string buffer to store the converted integer
 * @return The string buffer
 */
char* int_to_char(int number, char *strBuf)
{
    return int_to_char_b(number, strBuf, 10);
}

/**
 * Convert an integer to a char*
 * @param number The integer to convert
 * @param strBuf The string buffer to store the converted integer
 * @param base The base of the integer
 * @return The string buffer
 */
char* int_to_char_b(int number, char *strBuf, int base)
{
    int i = 0;
    bool isNegative = false;

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
        isNegative = true;
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