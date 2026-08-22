NAME = codexion
CC = cc
CFLAGS = -Wall -Wextra -Werror
HEADERS = codexion.h
SRCS = main.c \
	init.c \
	parser.c \
	dongles.c \
	dongle_utils.c \
	person.c \
	monitor.c \
	heap.c \
	heap_utils.c \
	utils.c \
	log_utils.c \
	clean_utils.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o:%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re