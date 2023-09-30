#include "ft_printf.h"

int ft_printf(const char *format, ...)
{
	int count;
	va_list args;

	// Define an array of characters for hexadecimal digits
	const char *HEX_DIGITS_LOWER = "0123456789abcdef";
	const char *HEX_DIGITS_UPPER = "0123456789ABCDEF";
	
	count = 0;
	va_start(args, format);

	while (*format)
	{
		if (*format == '%')
		{
			format++; // Move past '%'

			// Handle format specifiers
			if (*format == 'c')
			{
				// Handle %c
				char c = va_arg(args, int);

				write(1, &c, 1); // Print 'c' using the write function
				count++; // Update the character count
			}

			else if (*format == 's')
			{
				// Handle %s
				unsigned int len;
				char *str = va_arg(args, char *);

				len = ft_strlen(str); // Get the length of the string
				write(1, str, len); // Print 'str' using the write function
				count += len; // Update the character count
			}

			else if (*format == 'p')
			{
				// Handle %p (pointer)
				void *ptr = va_arg(args, void *);
				
				// Write "0x" to indicate a pointer value in hexadecimal
				write(1, "0x", 2);
				count += 2;

				// Cast the pointer to an unsigned long long for printing
				printDigits((unsigned long long)ptr, HEX_DIGITS_LOWER);
			}

			else if (*format == 'd' || *format == 'i')
			{
				// Handle %d and %i (signed decimal integers)
				int num;
				int isNegative;
				
				num = va_arg(args, int);
				isNegative = 0; // Check if the number is negative
				if (num < 0)
				{
					isNegative = 1;
					num = -num; // Make num positive for further processing
				}

				if (isNegative)
				{
					write(1, "-", 1); // Print the negative sign for negative numbers
					count++;
				}

				if (num == 0)
				{
					write(1, "0", 1); // Handle the case of num being zero
					count++;
				}
				else
					printDigits(num, NULL); // Call the helper function to print decimal digits
			}

			else if (*format == 'u')
			{
				// Handle %u (unsigned decimal integer)
				unsigned int num;
				
				num = va_arg(args, unsigned int);
				if (num == 0)
				{
					write(1, "0", 1); // Handle the case of num being zero
					count++;
				}
				else
					printDigits(num, NULL); // Call the helper function to print decimal digits
			}

			else if (*format == 'x' || *format == 'X')
			{
				// Handle %x (unsigned hexadecimal integer, lowercase) and %X (uppercase)
				unsigned int num;
				
				// Use the array of chars to express the hex upper/lower cases
				const char *hexDigits = (*format == 'x') ? HEX_DIGITS_LOWER : HEX_DIGITS_UPPER;

				num = va_arg(args, unsigned int);
				if (num == 0)
				{
					write(1, "0", 1); // Handle the case of num being zero
					count++;
				}
				else
					printDigits(num, hexDigits); // Call the helper function to print hexadecimal digits

			}

			else if (*format == '%')
			{
				// Handle %%
				write(1, "%", 1); // Print '%' character
				count++; // Update the character count
			}
		}

		else
		{
			// Handle non-% characters
			write(1, format, 1); // Print the character using the write function
			count++; // Update the character count
		}

		format++; // Move to the next character in the format string
	}

	va_end(args); // Clean up the va_list
	return count; // Return the total characters printed
}
