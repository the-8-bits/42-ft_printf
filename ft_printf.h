
#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h> // for the veriadic arguments handling
#include <unistd.h> // for the write function


/* Remodeled `printf` function, handles `%c`, `%s`, `%p`, `%d`, `%u`, `%x`, `%X`, `%%`, don´t handle
 * any buffer for better I/O efficiency*/
int     ft_printf(const char *format, ...);

/* Is a recursive function that prints the digits of an unsigned long long integer `n` either in
 * decimal or hexadecimal format. It has two main modes of operation:
 - Decimal Mode: If the `hexDigits` parameter is `NULL`, the function operates in decimal mode
   and prints the digits of `n` in base 10 (decimal).
 - Hexadecimal Mode: If the `hexDigits` parameter is not `NULL`, the function operates in
   hexadecimal mode and prints the digits of `n` in base 16 (hexadecimal). */
void printDigits(unsigned long long n, const char hexDigits);

/* This function returns the lengh of the string */
unsigned int ft_strlen(char *str);


/* Print Functions*/


#endif