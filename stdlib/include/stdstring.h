/**
 * stdstring.h
 * Basic Operating System, String Utilities
 */

/**
 * Get the length of a string
 * @param str The string to check the length of
 * @return The length of the given string
 */
int strlen(const char* str);

/**
 * Compare two strings lexicographically
 * @param s1 The first string
 * @param s2 The second string
 * @return s1 < s2 = -1, s1 == s2 = 0, s1 > s2 = 1
 */
int strcmp(const char* s1, const char* s2);