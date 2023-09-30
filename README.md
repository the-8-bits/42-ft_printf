---
title: ft_printf
tags:
  - "42"
  - programação
  - common_core
use: README, Documentation
languages: C
dependences:
---

<p align="center">
  <picture>
	<img alt="List_logo" src="https://drive.google.com/uc?export=view&id=1rFqWh4miOnHABWGa2X7KTe2geXDhuD2S">
  </picture>
</p>

# <p align="center">**ft_printf**</p>
<p align="center">Because ft_putnbr() and ft_putstr() aren’t enough</p>
</br>
<p align="center"> <i>Summary:</br>
	The goal of this project is pretty straightforward. You will recode `printf()`.</br>
	You will mainly learn about using a variable number of arguments. How cool is that??</br>
	It is actually pretty cool</i> 🙂</br>
	Version: 9.2</br>
</p>

</br>

> [!INFO] 
> If you spot something that isn't right, please open an [Issue](https://github.com/the-8-bits/42-libft/issues/new)

</br>

<details><summary>Table of Contents 🔖</summary>

- [**ft\_printf**](#ft_printf)
	- [Important Concepts](#important-concepts)
		- [Variadic Functions](#variadic-functions)
		- [`ar` commands](#ar-commands)
	- [Requirements](#requirements)
		- [Don’t implement the buffer management of the original `printf()`](#dont-implement-the-buffer-management-of-the-original-printf)
		- [Your function has to handle the following conversions: `cspdiuxX%`](#your-function-has-to-handle-the-following-conversions-cspdiuxx)
		- [Your function will be compared against the original `printf()`](#your-function-will-be-compared-against-the-original-printf)
		- [You must use the command `ar` to create your library](#you-must-use-the-command-ar-to-create-your-library)
		- [Using the `libtool` command is forbidden](#using-the-libtool-command-is-forbidden)
		- [Your `libftprintf.a` has to be created at the root of your repository](#your-libftprintfa-has-to-be-created-at-the-root-of-your-repository)
	- [Mandatory Part](#mandatory-part)
		- [Possible improvements and considerations](#possible-improvements-and-considerations)
	- [Bonus Part](#bonus-part)
		- [Manage any combination of the following flags: ’-0.’ and the field minimum width under all conversions](#manage-any-combination-of-the-following-flags--0-and-the-field-minimum-width-under-all-conversions)
		- [Manage all the following flags: `#`, `+`, *`(space)`*](#manage-all-the-following-flags---space)
		- [Main changes](#main-changes)
	- [Usage examples](#usage-examples)

</details>

---

## Important Concepts

### [Variadic Functions](../../../../Languages/C/README.md#variadic-functions)

They provide a versatile way to define functions that **can accept a variable number of arguments**. These functions allow developers to create flexible and efficient code by accommodating different argument counts at runtime. Unlike regular functions, which have a fixed parameter list, variadic functions use the ellipsis notation (`...`) to indicate that they can accept a variable number of arguments of varying types.

Here's a brief example of a variadic function that calculates the sum of its arguments:

```c
#include <stdarg.h>

int sum(int num, ...) {
	va_list args;
	va_start(args, num);
	
	int total = 0;
	for (int i = 0; i < num; i++) {
		total += va_arg(args, int);
	}
	
	va_end(args);
	return total;
}
```

The main used elements, that are essential when working with variadic functions in C, enable you to access and manipulate variable arguments in a safe and controlled manner, making it possible to write functions that accept a variable number of arguments.

- `va_list args`
- `va_start(args, num)
- `va_arg(args, type)`
- `va_end(args)`

### [`ar` commands]((../../../../Languages/C/README.md#ar-commands))

Is typically used for creating and manipulating static libraries in Unix-like operating systems, including Linux. A static library is a collection of object files (compiled code) bundled together into a single file that can be linked with a program at compile time.

---

## Requirements

### Don’t implement the buffer management of the original `printf()`

It means that you should focus on reproducing the formatting and output functionality of the `printf()` function without dealing with the internal buffering mechanisms that `printf()` uses to optimize I/O operations. These mechanisms are designed to reduce the number of system calls or actual writes to the output device (e.g., console, file), which can be slow and inefficient. Instead of writing each character individually, `printf()` collects a block of data in a buffer and then writes this buffer to the output device in larger chunks, reducing the overhead of system calls.

Here's how `printf()` typically uses internal buffering and how you can avoid it:

1. **Buffer Allocation**: `printf()` allocates an internal buffer (usually a character array) to store the formatted output before writing it to the output device. The size of this buffer can vary depending on the implementation but is often a reasonable size, like a few kilobytes.

2. **Partial Writes**: As you call `printf()` with various format specifiers and arguments, it formats the data and places it into this internal buffer. It doesn't immediately write to the output device for each call to `printf()`. Instead, it accumulates data in the buffer.

3. **Flush Operation**: When the internal buffer is full or when a newline character (`'\n'`) is encountered (for line buffering), or when you explicitly call `fflush(stdout)` or `fprintf(file, ...)` functions, `printf()` flushes the buffer. This means it writes the entire contents of the buffer to the output device in one go.

To avoid these internal buffering mechanisms, and write data directly without buffering, you have a few options:

- **Output Formatting**: You should implement the logic to parse the format string and handle the various format specifiers (e.g., `%d`, `%s`, `%f`) correctly. Your custom `printf` function should format the output as specified in the format string.

- **Writing to Output**: After formatting the output, your custom `printf` function should write the formatted data directly to the output stream (usually the console or a file) without worrying about buffering.

- **No Internal Buffer**: Unlike the original `printf()`, which often uses an internal buffer to collect formatted output before writing it to the output stream, your custom implementation should skip this buffering step. In other words, the output should be sent immediately to the output stream as soon as it's formatted.
	> You can use the `write()` system call to write data directly to the output file descriptor (e.g., `stdout`, a file). This bypasses any internal buffering mechanisms entirely. However, this approach requires manual formatting and lacks the convenience of format specifiers.

- **I/O Efficiency**: While you won't implement buffering, you should still aim for I/O efficiency. Writing one character at a time to the output stream can be inefficient. So, you may want to use system calls or library functions that offer efficient I/O operations for writing data.

By omitting the buffer management aspect, you simplify your custom `printf` implementation, but it may be less efficient in terms of I/O compared to the original `printf()` which buffers data before sending it to the output stream. However, this trade-off can be acceptable in some situations where simplicity and clarity of code are more important than optimal performance.

> Make cleaner not faster code...

### Your function has to handle the following conversions: `cspdiuxX%`

It means that your custom `printf` function should be capable of formatting and displaying values of various data types corresponding to these conversion characters. Here's what each of these conversion characters represents:

- **`c`**: Character conversion.
   - `%c` in the format string is used to display a single character.

- **`s`**: String conversion.
   - `%s` is used to display a null-terminated character array (string).

- **`p`**: Pointer conversion.
   - `%p` is used to display a pointer's value, typically representing a memory address, in hexadecimal format.

- **`d` and `i`**: Decimal and integer conversion.
   - `%d` and `%i` are used to display signed decimal integers in base 10.

- **`u`**: Unsigned integer conversion.
   - `%u` is used to display unsigned (base 10) decimal integers.

- **`x` and `X`**: Hexadecimal conversion.
   - `%x` is used to display unsigned hexadecimal (base 16) integers in lowercase.
   - `%X` is used to display unsigned hexadecimal (base 16) integers in uppercase.

- **`%`**: Percent character itself.
   - `%%` is used to display a literal percent character in the output.

### Your function will be compared against the original `printf()`

> Okay.

### You must use the command `ar` to create your library

Allows you to create a static library that can be linked with multiple C programs. Static libraries are linked at compile time, which means the code from the library is copied into the executable, making it self-contained and independent of the library's presence on the system where the program is run.

### Using the `libtool` command is forbidden

It means that you should not use the GNU Libtool utility for building libraries in your project. Libtool is a powerful tool that simplifies the creation of shared libraries (dynamic libraries) on various Unix-like systems. It provides a higher level of abstraction for handling the complexities of shared libraries, including platform-specific differences.

Here's why you might be forbidden from using `libtool`:

1. **Simplicity**: In some cases, the use of `libtool` might be considered overkill for a project that only requires static libraries or has simple library needs. `libtool` can introduce additional complexity and dependencies that are unnecessary for such projects.

2. **Project Constraints**: Your project or assignment instructions may specify that you should not use `libtool` to ensure that you learn and demonstrate an understanding of the lower-level library creation and linking process using tools like `ar` and `gcc` directly.

3. **Compatibility**: `libtool` is primarily designed for creating shared libraries. If your project or platform doesn't require shared libraries and static libraries are sufficient, using `ar` and `gcc` directly can be more straightforward and compatible.

### Your `libftprintf.a` has to be created at the root of your repository

When you're instructed that your `libftprintf.a` has to be created at the root of your repository, it means that the static library you are building (in this case, `libftprintf.a`) should be placed in the top-level directory of your project's repository.

1. **Static Library Name**: `libftprintf.a` is the name of the static library you are building. Static libraries typically have the `.a` file extension on Unix-like systems.

2. **Root of Your Repository**: The "root" or "top-level" directory of your repository is the main directory that contains all the project's source code, files, and directories. It's the directory where your project's version control system (e.g., Git) is initialized.

Placing the library in the root of your repository makes it easily accessible to other parts of your project. This is typically done to ensure that other source files and build scripts can reference and link with `libftprintf.a` without specifying a complex or relative path.

Your project structure should look like this:

```
/ft_printf
	├── src
	│   ├── ft_printf.c
	│   ├── ...
	├── include
	│   ├── ft_printf.h
	│   ├── ...
	├── Makefile
	├── libftprintf.a   <-- This is where you should place it
	├── ...
```

---

## Mandatory Part

This function takes a format string and a variable number of arguments and prints formatted output to the standard output (`stdout`). It handles format specifiers such as characters, strings, signed integers and unsigned integers, hexadecimal integers, and printing a literal '%' character. The code uses `va_list` and `va_arg` to process the variable arguments.

```c
// ft_printf.c
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
		// Handle format specifiers
		if (*format == '%')
		{
			format++; // Move past '%'

			// Handle %c
			if (*format == 'c')
			{
				// Handle %c
				char c = va_arg(args, int);
				// Implement printing 'c' here
				count++; // Update the character count
			}
			
			// Handle %s
			else if (*format == 's')
			{/* ... */}
			
			// Handle %p (pointer)
			else if (*format == 'p')
			{/* ... */}
			
			// Handle %d and %i (signed decimal integers)
			else if (*format == 'd' || *format == 'i')
			{/* ... */}
			
			// Handle %u (unsigned decimal integer)
			else if (*format == 'u')
			{/* ... */}
			
			// Handle %x (unsigned hexadecimal integer, lowercase) and %X (uppercase)
			else if (*format == 'x' || *format == 'X')
			{/* ... */}
			
			// Handle %%
			else if (*format == '%')
			{/* ... */}
		}
		else
		{
			// Handle non-% characters
			// Implement printing them here (you may use write function)
			count++; // Update the character count
		}
		format++; // Move to the next character in the format string
	}

	va_end(args); // Clean up the va_list
	return count; // Return the total characters printed
}
```

### Possible improvements and considerations

- Error handling: The code does not handle invalid format specifiers gracefully. It should include error checking and report any invalid format specifiers or missing arguments.
- Precision and width: The code does not handle precision or width modifiers (e.g., `%10s`, `%.2f`) commonly found in `printf`. Adding support for these would make the function more versatile.
- Buffering: Instead of using `write` for every character, you can consider buffering the output and writing in larger chunks for better performance.
- Error reporting: It might be helpful to return an error code or use a separate mechanism to report errors or failures during printing.
- Portability: The code assumes that `write` is available and writes to standard output. You may want to make it more portable or allow specifying the output stream.
- Extensibility: If you plan to add more format specifiers or customization options, consider a more modular design to make future additions easier.


---

## Bonus Part

```c
// Handle %d and %i (signed decimal integers)
else if (*format == 'd' || *format == 'i')
{
	/* ... */
	while (*format == '#' || *format == '+' || *format == ' ' || *format == '-' || *format == '0')
	{/* ... */}			
}
```

### Manage any combination of the following flags: ’-0.’ and the field minimum width under all conversions

The field minimum width is a formatting feature in the `printf` family of functions that allows you to specify the minimum number of characters that should be printed for a particular argument. This feature ensures that the output is padded or aligned to meet this width requirement. It is typically specified using an optional width specifier in the format string and can be combined with other formatting flags.

Here's how it works:

1. **Width Specifier**: In the format string, you can specify the minimum width by using an asterisk (`*`) followed by an integer value or by directly specifying the integer value. For example:
   
   - `*` specifies that the width should be obtained from the argument list.
   - `3` specifies a fixed width of 3 characters.

2. **Padding and Alignment**: Depending on the flags used in combination with the width specifier, the output can be padded with spaces or zeros to meet the specified width. The commonly used flags are:

   - `-` (Minus): Left-justify the output within the specified width. This means that extra spaces are added to the right to reach the specified width.
   - `0` (Zero): Pad the output with leading zeros instead of spaces. This flag is typically used with numeric values.
   
   If neither of these flags is used, the default behavior is to right-justify the output, adding spaces to the left to meet the specified width.

**Examples:**

- `%5d`: This specifies a minimum width of 5 characters for a decimal integer. If the integer is shorter than 5 characters, it will be right-justified with leading spaces.

- `%-8s`: This specifies a minimum width of 8 characters for a string. If the string is shorter than 8 characters, it will be left-justified with trailing spaces.

- `%06.2f`: This specifies a minimum width of 6 characters for a floating-point number with 2 decimal places. If the number is shorter than 6 characters, it will be padded with leading zeros.

In the `ft_printf` function, when it encounters a format specifier like `%5d`, it need to parse the specifier to extract the width (`5` in this case) and any flags (such as `-` or `0`). Then, you should adjust the output accordingly, either by adding spaces or zeros to meet the specified width, depending on the flags.

> [!INFO]
> The width specifier is optional, and if it's not provided, no padding or alignment is performed. It's a useful feature for formatting output to align columns or ensure a consistent appearance in tables and reports.

### Manage all the following flags: `#`, `+`, *`(space)`*

The flags `#`, `+`, and space are formatting options that you can use with format specifiers in the `printf` family of functions (including `ft_printf`) to control the way certain types of data are formatted in the output. These flags are used to modify the behavior of specific conversion specifiers, such as `%d`, `%o`, `%x`, and `%f`. Here's an explanation of each of these flags:

1. **`#` (Sharp or Hash)**

	- **Usage**: The `#` flag is used with various format specifiers to modify the format of the output.
	
	- **Effects**: The specific effect of the `#` flag depends on the conversion specifier it is used with. Here are some common uses:
		- `%x` and `%X` (Hexadecimal): When used with `%x` or `%X`, the `#` flag adds the "0x" or "0X" prefix to the hexadecimal representation of the number. For example, `%#x` would print "0x" before the hexadecimal value.
		- `%o` (Octal): When used with `%o`, the `#` flag adds a leading zero to the octal representation to indicate that it's an octal number. For example, `%#o` would print "0" before the octal value.
		- `%f` (Floating-Point): When used with `%f`, the `#` flag ensures that the output has a decimal point, even if there are no fractional digits. For example, `%#f` would print "3.0" for the number 3.

2. **`+` (Plus)**

	- **Usage**: The `+` flag is used with numeric format specifiers, such as `%d` and `%f`.
	
	- **Effects**: When used with numeric format specifiers, the `+` flag ensures that the output includes a sign character for both positive and negative numbers:
		- `%d` and `%i` (Decimal Integer): For these specifiers, the `+` flag ensures that a `+` sign is printed before positive numbers.
		- `%f` (Floating-Point): When used with `%f`, the `+` flag ensures that both positive and negative numbers are printed with a sign character. Positive numbers have a `+` sign, while negative numbers have the regular `-` sign.

3. **Space**

	- **Usage**: The space flag is used with numeric format specifiers, such as `%d` and `%f`.
	
	- **Effects**: When used with numeric format specifiers, the space flag ensures that positive numbers are preceded by a space character (if no sign is present) to align them with negative numbers:
		- `%d` and `%i` (Decimal Integer): For these specifiers, the space flag adds a space character before positive numbers if no sign is present. For example, `% d` would print " 3" for the number 3.
		- `%f` (Floating-Point): When used with `%f`, the space flag ensures that positive numbers are printed with a space character before the sign if no sign is present. For example, `% f` would print " 3.0" for the number 3.

In the `ft_printf` function, when it encounters a format specifier like `%+d` or `% #x`, it needs to parse the specifier to identify and apply these flags accordingly to achieve the desired output formatting. These flags provide options for controlling the display of numeric and other data types in a formatted manner.

### Main changes

Let's break down the differences and updates made to the `else if (*format == 'd' || *format == 'i')` condition in order to allow a more versatile formatting of signed decimal integers. It introduces **width specification**, **flag handling**, and **padding / alignment options** to meet various formatting requirements while maintaining compatibility with the original behavior of `%d` and `%i` format specifiers.

1. **Handling Flags:**
	
	In the updated condition, we check for the presence of various flags that can modify the formatting of the output. Flags such as `#`, `+`, space, `-`, and `0` are checked and stored in the `flag` variable. The presence of these flags influences how the number is printed.

2. **Width Specification:**
	
	We added a new section that parses and stores the width specifier in the `width` variable. The width specifier determines the minimum width of the printed output. It is obtained by parsing digits from the format string.

3. **Padding and Alignment:**
	
	Based on the presence of flags and the specified width, we calculate `paddingLength`, which represents the number of characters needed to reach the specified width. Depending on whether the `-` flag is present, we either left-justify the output by adding spaces or zeros to the right (default behavior) or right-justify it by adding spaces or zeros to the left.
	
	- If the `-` flag is present, we left-justify the output. This means we add spaces or zeros to the right to meet the specified width.
	
	- If the `-` flag is not present, we right-justify the output. In this case, we handle the sign character (if needed) and then add spaces or zeros to the left to meet the specified width.

4. **Sign Handling:**

	We handle the sign character for negative and positive numbers based on the presence of the `+` and `-` flags. The sign character is added to the output when necessary.
	
	- For positive numbers, the `+` flag adds a `+` sign character.
	- For positive numbers without a sign, the space flag adds a space character.
	- For negative numbers, the `-` flag ensures that the `-` sign is correctly positioned.

5. **Padding Character:**

	We determine the padding character (`paddingChar`) based on the presence of the `0` flag. If the `0` flag is present, we use '0' as the padding character; otherwise, we use a space character.

6. **Output Adjustment:**

	We adjust the output format based on the specified width, flags, and sign characters. This ensures that the output meets the desired formatting requirements.

7. **Continued Digits Printing:**

	After handling width, flags, and sign characters, the code continues with the existing logic for printing the actual digits of the number, which was already present in the previous responses.
	

---

## Usage examples

Certainly, here are usage examples for each of the scenarios you've listed based on the format specifiers and conditions:

1. **`%c`: Character**

```c
char ch = 'A';
ft_printf("Character: %c\n", ch);
```

2. **`%s`: String**

```c
char *str = "Hello, World!";
ft_printf("String: %s\n", str);
```

3. **`%p`: Pointer**

```c
void *ptr = &ch;
ft_printf("Pointer: %p\n", ptr);
```

4. **`%d` and `%i`: Signed Decimal Integer**

```c
int num = 42;
ft_printf("Integer: %d\n", num);
```

5. **`%u`: Unsigned Decimal Integer**

```c
unsigned int num = 42;
ft_printf("Unsigned Integer: %u\n", num);
```

6. **`%x` and `%X`: Hexadecimal Integer (lowercase and uppercase)**

```c
int hex_num = 255;
ft_printf("Hexadecimal (lowercase): %x\n", hex_num);
ft_printf("Hexadecimal (uppercase): %X\n", hex_num);
```

7. **`%%`: Percentage Sign**

```c
ft_printf("This is a literal %% character.\n");
```

In the `./tests/` folder there're some shell scripts implementing these scenarios.


> Malebolge