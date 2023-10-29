# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: matde-je <matde-je@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/03 20:20:01 by matde-je          #+#    #+#              #
#    Updated: 2023/10/29 23:06:35 by matde-je         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SOURCES = main.c create.c end_time.c messages.c threads.c eat.c

OBJECTS	=	$(SOURCES:.c=.o)
CC	=	cc -Wall -Wextra -Werror -g -pthread -fsanitize=thread

all:		$(NAME)

$(NAME):	$(OBJECTS)
			$(CC) $(OBJECTS) -o $(NAME)

clean:		
			rm -f $(OBJECTS)

fclean:		clean
			rm -f $(NAME)

re:			fclean $(NAME)

.PHONY:	all clean fclean re