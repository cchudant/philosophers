CC = gcc
CFLAGS = -g -Wall -Wextra -Werror -pthread
NAME = philo_one
HEADERS = philo.h
OBJECTS = main.o monitor.o philo.o philo2.o utils.o utils2.o

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(HEADERS) $(OBJECTS)
	gcc $(CFLAGS) $(OBJECTS) -o $(NAME)

clean:
	rm -f $(OBJECTS) $(BONUS_OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all
