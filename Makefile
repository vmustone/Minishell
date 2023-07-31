# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vmustone <vmustone@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/27 17:26:10 by vmustone          #+#    #+#              #
#    Updated: 2023/07/31 17:10:49 by vmustone         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT = libft/libft.a

SRC = main.c signals/signals.c builtins/ft_cd.c builtins/ft_env.c builtins/ft_pwd.c\
		builtins/ft_export.c env/env_init.c builtins/ft_unset.c builtins/ft_echo.c\
		builtins/ft_exit.c

OBJ = $(SRC:.c=.o)

O_FLAGS = -lreadline -L${HOME}/.brew/opt/readline/lib

C_FLAGS = -I${HOME}/.brew/opt/readline/include

FLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(LIBFT):
	make -C libft

$(NAME): $(LIBFT) $(OBJ)
	cc $(FLAGS) $(C_FLAGS) $(O_FLAGS) $(OBJ) $(LIBFT) -o $(NAME)

clean:
	rm -f $(OBJ)
	make clean -C libft

fclean: clean
	rm -f $(NAME) $(LIBFT)

%.o: %.c
	cc $(FLAGS) $(C_FLAGS) -c $< -o $@

re: fclean all
