NAME = libft.a
CFLAGS = -Wall -Wextra -Werror
SRC = ft_isalpha.c \
ft_isdigit.c \
ft_isalnum.c \
ft_isascii.c \
ft_isprint.c \
ft_strlen.c
OBJ = $(SRC:.c=.o)
CC = cc
cc -Wall -Wextra -Werror ft_isalpha.c ft_isascii.c ft_strlen.c -I.