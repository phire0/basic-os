/**
 * stdio.h
 * Basic Operating System, Standard Input/Output
 */

/**
 * Clear all contents from the screen
 */
void clear_screen(void);

/**
 * Print a given message
 * @param str The string to print
 */
void kprint(char *str);

/**
 * Print a givem message using format modifiers
 * 
 */
void kprint_f(char *str, ...);

/**
 * Print a given message at the specified location
 * @param str The string to print
 * @param column Column output location
 * @param row Row output location
 */
void kprint_l(char *str, int column, int row);

/**
 * Print a given message at the specified location with attributes
 * @param str The string to print
 * @param column Column output location
 * @param row Row output location
 * @param attr Print attributes (such as colour), pass hex value or use pre_kprint_attr and COLOUR definitions
 */
void kprint_la(char *str, int column, int row, char attr);

/**
 * Quickly convert specified background/foreground colour values
 * into valid attr value for krpint_at
 * @param background the background colour, hex 0 to F or use colour defined in screen.h
 * @param foreground the foreground colour, hex 0 to F or use colour defined in screen.h
 * @return The proper hex value with the chosen attributes
 */
char pre_kprint_attr(char background, char foreground);