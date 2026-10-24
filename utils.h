#ifndef UTILS_H
#define UTILS_H

/** checks the validity of binary sequence, it must only contain 0s and 1s
 * or comma "," for multiple comma-separated binary sequences
 * @param *seq binary sequence string
 * @return 0 if valid
 *         1 if null pointer provided
 *         2 if the program argument -bs value is not provided
 *         3 if check_comma failed
 */
int check_sequence(const char *seq);

/** checks if comma is well placed in the sequence, the comma must not 
 * start or end the sequence, more than one contiguous commas are
 * not allowed
 * @param *seq binary sequence string
 * @return 0 if valid
 *         1 if not valid
 */
int check_comma(const char *seq);

/** replaces the placeholder "@" with the current index character
 * in prefix template provided with the program argument -pf
 * @param *str template string
 * @param *strnew filled template string
 * @param index character index (0 => A, 1 => B, ...)
 * @return 0 if replacement done sucessfylly
 *         1 if template *str is null
 */
int replace_symbol(const char *str, char* strnew, int index);

/** returns the length of a string
 * @param *str string
 * @return 0 if empty or null string, otherwise the length of the string
 */
int slen(const char *str);

/** compares two strings
 * @param str1 first string
 * @param str2 second string
 * @return 0 if strings are identical
 *         1 if not identical
 */
int scmp(const char *str1, const char *str2);

/** copies a string to another
 * @param *dst destination string
 * @param *src source string
 */
void scpy(char *dst, const char *src);

/** checks if a string has a given character
 * @param *str the string to be checked
 * @param c the character to search for in the string
 * @return 0 if the character is found in the string
 *         1 if the character is not found
 */
int has_char(const char *str, const char c);

/** verifies the arguments against defined criteria and prints on stderr
 * if an input doesn't meet a criteria
 * 
 * Criteria: vh > vl, tr != 0, tf != 0, p != 0, p < (tf+tr), bseq must pass check_sequence, timeunit and voltageunit must be null or one of these characters: T, G, M, k, m, u, n, p, f.
 *
 * @param vl voltage low
 * @param vh voltage high
 * @param tr raising edge time
 * @param tf falling edge time
 * @param p period
 * @param timeunit time unit
 * @param voltageunit voltage unit
 * @param *bseq binary sequence
 * @return 0 if input is valid
 *         1 if error occured
 */
int verify_input(const double vl, const double vh, const double tr, const double tf, const double p, const char timeunit, const char voltageunit, const char *bseq);

/** prints help
 */
void printhelp();

#endif //UTILS_H
