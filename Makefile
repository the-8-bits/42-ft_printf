NAME    = libftprintf.a
CFLAGS  = -Wall -Werror -Wextra -I. -c

PART    = ft_printf.c
OBJ     = $(PART:.c=.o)

BONUS   = ft_printf_bonus.c
OBJ_BONUS = $(BONUS:.c=.o)

FILES   = $(PART) $(BONUS)
OBJ     = $(OBJ)$(OBJ_BONUS)

all: $(NAME)

$(NAME): $(OBJ)
    ar rcs $(NAME) $(OBJ)

# A generic rule to build object files (%.o: %.c) with automatic dependency generation
%.o: %.c
    gcc $(CFLAGS) $< -o $@

clean:
    rm -f $(OBJ)

fclean: clean
    rm -f $(NAME)

re: fclean all

# .PHONY targets for clean, fclean, all, and re for better Makefile behavior
.PHONY: clean fclean all re

# Add a target to run tests using the test.sh script
test: all
    sh ./tests/test.sh
