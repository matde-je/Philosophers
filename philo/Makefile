name = philo

src = statics.c main.c

obj = $(SRC:.c=.o)

cc = cc -Wall -Wextra -Werror -g fsanitize=address

all: $(NAME)

$(NAME):	$(OBJ)
			$(CC) $(OBJ) -o $(NAME)

clean:
			rm -f $(OBJ)

fclean:		clean
			rm -f $(NAME)

re: 		fclean $(NAME)

.PHONY: all clean fclean re
