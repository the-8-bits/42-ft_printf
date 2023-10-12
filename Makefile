# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gabrodri <gabrodri@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/12 19:53:25 by gabrodri          #+#    #+#              #
#    Updated: 2023/10/12 19:54:36 by gabrodri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libftprintf.a
# CFLAGS are flags passed to the compiler. -Wall -Werror -Wextra are used to
CFLAGS	= -Wall -Werror -Wextra -I. -c

# Part is the Mandatory files to submmit
MANDATORY		= ft_printf.c ft_printf_utils.c
MANDATORY_OBJ	= $(MANDATORY:.c=.o)

# This is the bonus part
BONUS   = ft_printf_bonus.c
BONUS_OBJ = $(BONUS:.c=.o)

# The rule to compile all the files
all: $(NAME)

# The rule to compile the library without the bonus
$(NAME): $(MANDATORY_OBJ)
# ar: create, replace, and index; -options
	@echo "------------------------------------"
	@echo "Compiling the Library (no bonus)"
	@echo "------------------------------------"
	ar -rc $(NAME) $(MANDATORY_OBJ) 

# The rule to compile the library with mandatory and bonus
bonus: $(BONUS_OBJ)
	@echo "------------------------------------"
	@echo "Compiling the Library (w/ bonus)"
	@echo "------------------------------------"
	ar -rc $(NAME) $(BONUS_OBJ) 

# Add a target to run tests using the test.sh script
#test: all
#	@echo "------------------------------------"
#	@echo "Running the tests of the project"
#	@echo "------------------------------------"
#	sh ./tests/test.sh

# The rule to clean the object files
clean:
	@echo "------------------------------------"
	@echo "Cleaning the object files"
	@echo "------------------------------------"
	rm -f $(MANDT_OBJ) $(BONUS_OBJ)

# The rule to clean the object files and the library
fclean: clean
	@echo "------------------------------------"
	@echo "Cleaning the object files and the library"
	@echo "------------------------------------"
	rm -f $(NAME)

# The rule to clean the object files, the library, and recompile
re: fclean all

# The rule to clean the object files, the library, and recompile with bonus
# .PHONY targets for clean, fclean, all, and re for better Makefile behavior
.PHONY: clean fclean all re
