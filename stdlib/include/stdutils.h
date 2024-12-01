/**
 * stdutils.h
 * Basic Operating System, Standard Utilities
 */

#ifndef _STDUTILS_H
#define _STDUTILS_H

/**
 * Convert an integer to a char*
 * @param number The integer to convert
 * @param strBuf The string buffer to store the converted integer
 * @return The string buffer
 */
char* int_to_char(int number, char *strBuf); 

/**
 * Convert an integer to a char*
 * @param number The integer to convert
 * @param strBuf The string buffer to store the converted integer
 * @param base The base of the integer
 * @return The string buffer
 */
char* int_to_char_b(int number, char *strBuf, int base); 

#endif