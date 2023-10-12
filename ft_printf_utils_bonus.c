/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrodri <gabrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 19:52:57 by gabrodri          #+#    #+#             */
/*   Updated: 2023/10/12 19:52:57 by gabrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

// Helper function to recursively print decimal and hexadecimal digits
void printDigits(unsigned long long n, const char hexDigits)
{
	if (n == 0)
		return;

	char digit; // Digit variable to store the current digit

	if (!(hexDigits == NULL))
	{ // Handles the hexdecimal numbers
		printDigits(n / 16, hexDigits);
		digit = hexDigits[n % 16];    
	}
	else
	{ // Handles the decimal numbers
		printDigits(n / 10, NULL);
		digit = '0' + (n % 10);
	}

	write(1, &digit, 1);
	count++;
}


// 




// Already in Libft
unsigned int	ft_strlen(char *str)
{
	const char *ptr;

	ptr = str;
	while (*ptr)
	{
		ptr++;
	}
	return (unsigned int)(ptr - str);
}