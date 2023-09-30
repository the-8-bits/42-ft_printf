---
title: ft_printf - Tests
tags:
  - "42"
  - programação
  - common_core
use: README, Documentation
languages: C
dependences: ft_printf
---


# Test Elements

## **Define Makefile Target**: 

   ```bash
   MAKE_TARGET="all"
   ```

   This line sets the Makefile target to be used when compiling the C code. The target specified here is "all," which is typically used to build the entire project.

## **Compile the Code**:

   ```bash
   PROGRAM="./a.out" make CC=cc CFLAGS="-Wall -Wextra -Werror" LDLIBS="-lftprintf" $MAKE_TARGET
   ```

   This line compiles the C code using the Makefile with specific compiler and flag settings. Here's what each part does:

   - `PROGRAM="./a.out"`: Specifies the name of the output program. In this case, it assumes the compiled program will be named "a.out."

   - `make`: Invokes the Makefile build process.

   - `CC=cc`: Sets the C compiler to "cc."

   - `CFLAGS="-Wall -Wextra -Werror"`: Sets compiler flags. `-Wall`, `-Wextra`, and `-Werror` enable various warning and error checks to ensure code quality.

   - `LDLIBS="-lftprintf"`: Specifies the library to link with (assuming it's named "libftprintf.a").

   - `$MAKE_TARGET`: Specifies the Makefile target to build, which was set to "all."

## **Check Compilation Success**:

   ```bash
   if [ $? -eq 0 ]; then
       echo "Compilation successful."
   else
       echo "Compilation failed. Exiting."
       exit 1
   fi
   ```

   This block of code checks whether the compilation was successful. If the compilation returns an exit code of 0 (which indicates success), it prints "Compilation successful." Otherwise, it prints "Compilation failed" and exits with a status code of 1.

## **Define Test Cases**:

   The script defines two arrays, `MANDATORY_CASES` and `BONUS_CASES`, which store the test cases to be executed. Each test case is a command that runs the compiled program with specific arguments and format strings.

## **Run Test Cases**:

   The script iterates through the test cases and executes them using the `eval` command. It separates the execution of mandatory and bonus test cases and provides informative output for each test case.

## **Clean Up**:

   ```bash
   make clean
   ```

   After running all test cases, the script cleans up by executing `make clean`. This removes any generated object files and executable files.

# **How to Use the Script**:

1. Save the script to a file (e.g., `./tests/test.sh`) in the same directory as your project's Makefile and C source code.

2. Make the script executable using the command: `chmod +x ./tests/test.sh`.

3. Open a terminal and navigate to the directory containing the script.

4. Execute the script by running: `./tests/test.sh`.

   The script will compile your code, run the defined test cases, and display the results. It will check for compilation success and provide information about each test case's execution. If any test case fails, you'll be alerted with an error message.