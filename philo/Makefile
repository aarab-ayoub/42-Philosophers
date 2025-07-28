CC = cc 
NAME = philo
CFLAGS = -Wall -Wextra -Werror -pthread #-g3 -fsanitize=address

SRCS = main.c init.c parsing.c philosopher.c utils/ft_atoi.c utils/utils.c monitor.c actions.c forks.c

OBJS = $(SRCS:.c=.o)

all: $(NAME) clean

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS) ./a.out

fclean: clean
	rm -f $(NAME)

re: fclean all
