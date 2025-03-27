# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gualvare <gualvare@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/27 18:21:50 by gualvare          #+#    #+#              #
#    Updated: 2025/03/27 18:23:40 by gualvare         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=thread
SRC = main.c init.c philosophers.c monitor.c arg_checker.c
OBJ = $(SRC:.c=.o)
HEADER = philo.h

all: $(NAME)

$(NAME): $(OBJ) $(HEADER) Makefile
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -lpthread

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
