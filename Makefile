NAME = minishell

CC = cc

SRC = buildin.c ft_strcmp.c

OBJ = ${SRC:.c=.o}

%.o: %.c
	$(CC) -Wall -Wextra -Werror -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(OBJ) -lreadline -o $(NAME) -fsanitize=address

all: $(NAME)

clean:
	rm -f ${OBJ}

fclean: clean
	rm -f $(NAME)

re: fclean all
