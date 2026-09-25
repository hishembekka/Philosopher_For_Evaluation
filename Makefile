NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
CPPFLAGS = -I.

SRCS = main.c \
	parsing.c \
	init.c \
	simulation.c \
	sync.c \
	routine.c \
	actions.c \
	forks.c \
	monitor.c \
	print.c \
	time.c \
	utils.c \
	clear.c

OBJS = $(SRCS:.c=.o)
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c philo.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
