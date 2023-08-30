# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: matilde <matilde@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/28 11:26:11 by matilde           #+#    #+#              #
#    Updated: 2023/08/30 17:29:56 by matilde          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = main.c time_end.c init.c threads.c actions.c

OBJ = $(SRC:.c=.o)

CC = cc -Wall -Wextra -Werror -g -pthread #-fsanitize=address

all: $(NAME)

$(NAME):	$(OBJ)
			$(CC) $(OBJ) -o $(NAME)

clean:
			rm -f $(OBJ)

fclean:		clean
			rm -f $(NAME)

re: 		fclean $(NAME)

.PHONY: all clean fclean re
