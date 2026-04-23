NAME = libftprintf.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -I. -Ilibft
SRC = ft_printf.c \
	ft_printchar.c \
	ft_printstr.c \
	ft_printvoid.c \
	ft_puthex_base.c \
	ft_printint.c \
	ft_printunint.c \
	ft_printhex_x.c \
	ft_printhex_up.c

OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft
	ar rcs $(NAME) $(OBJ) libft/*.o

clean:
	rm -f $(OBJ)
	make -C libft clean

fclean: clean	
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re