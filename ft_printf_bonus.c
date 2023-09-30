#include "ft_printf_bonus.h"

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
		// Handle format specifiers
		if (*format == '%')
		{
			format++; // Move past '%'

			// Handle %c
			if (*format == 'c')
			{
				char c = va_arg(args, int);

				write(1, &c, 1); // Print 'c' using the write function
				count++; // Update the character count
			}

			// Handle %s
			else if (*format == 's')
			{
				unsigned int len;
				char *str = va_arg(args, char *);

				len = ft_strlen(str); // Get the length of the string
				write(1, str, len); // Print 'str' using the write function
				count += len; // Update the character count
			}

			// Handle %p (pointer)
			else if (*format == 'p')
			{
				void *ptr = va_arg(args, void *);
				
				// Write "0x" to indicate a pointer value in hexadecimal
				write(1, "0x", 2);
				count += 2;

				// Cast the pointer to an unsigned long long for printing
				printDigits((unsigned long long)ptr, HEX_DIGITS_LOWER);
			}

			// Handle %d and %i (signed decimal integers)
			else if (*format == 'd' || *format == 'i')
			{
				int num;
				int width;
				int isNegative;
							
				num = va_arg(args, int);

				// Check for the presence of flags
				width = 0;
				char flag = '\0';

				// Check for flags (#, +, space, -, 0)
				while (*format == '#' || *format == '+' || *format == ' ' || *format == '-' || *format == '0')
				{
					flag = *format;
					format++;
				}

				// Check if the width is specified
				while (*format >= '0' && *format <= '9')
				{
					width = width * 10 + (*format - '0');
					format++;
				}

				// Calculate the number of characters needed to reach the specified width
				int paddingLength;

				paddingLength = width - count; // 'count' is the current character count
				if (paddingLength > 0)
				{
					char paddingChar = (flag == '0') ? '0' : ' '; // Determine padding character

					// Check for the '-' flag for left-justification
					if (flag == '-')
					{
						// Left-justify the output by adding spaces or zeros to the right
						while (paddingLength > 0)
						{
							write(1, &paddingChar, 1);
							count++;
							paddingLength--;
						}
					}
					else
					{
						// Right-justify the output by adding spaces or zeros to the left
						char outputChar;
						
						// Sign handling and digit printing
						int isNegative;

						isNegative = 0; // Check if the number is negative
						if (num < 0)
						{
							// Handle the sign character for negative numbers
							outputChar = '-';
							
							num = -num; // Make num positive for further processing
							isNegative = 1;
							
							width--; // Reduce the width to account for the sign character
						}
						else if (flag == '+')
						{
							// Handle the sign character for positive numbers with '+'
							outputChar = '+';
							width--; // Reduce the width to account for the sign character
						}
						else if (flag == ' ')
						{
							// Handle the space character for positive numbers with ' '
							outputChar = ' ';
							width--; // Reduce the width to account for the space character
						}
						else
						{
							// No sign character, use padding character
							outputChar = paddingChar;
						}

						// Right-justify by adding spaces or zeros to the left
						while (paddingLength > 0)
						{
							write(1, &paddingChar, 1);
							count++;
							paddingLength--;
						}

						// Print the sign character or padding character (if needed)
						write(1, &outputChar, 1);
						count++;
					}
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

			// Handle %u (unsigned decimal integer)
			else if (*format == 'u')
			{
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

			// Handle %x (unsigned hexadecimal integer, lowercase) and %X (uppercase)
			else if (*format == 'x' || *format == 'X')
			{
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

			// Handle %%
			else if (*format == '%')
			{
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
