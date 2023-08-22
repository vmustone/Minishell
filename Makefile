# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vmustone <vmustone@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/10 20:18:39 by lbroms            #+#    #+#              #
#    Updated: 2023/08/22 15:30:55 by vmustone         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT = libft/libft.a

SRC = minishell.c allocations.c lexer.c minishell_main_utils.c \
	shell_error.c shell_ft_strdup.c split_shell_input.c create_tokens_utils.c \
	split_shell_utils.c split_shell_utils_2.c  create_tokens.c shell_ft_substr.c \
	parser.c parse_utils.c parse_utils_2.c parse_utils_3.c shell_ft_split.c \
	shell_ft_strjoin.c executer.c executer_utils.c \
	ft_cd.c ft_echo.c ft_env.c ft_exit.c ft_export.c ft_pwd.c ft_unset.c \
	env_file.c executer_utils_2.c parser_utils4.c shell_ft_itoa.c \
	check_for_arrangement_errors.c singnals.c executer_utils_3.c \
	create_tokens_utils_2.c split_shell_input_utils_3.c signal_utils.c \
	here_doc.c split_shell_utils_4.c set_epx.c

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wunused-function -Werror -Wextra

O_FLAGS = -lreadline -L${HOME}/.brew/opt/readline/lib

C_FLAGS = -I${HOME}/.brew/opt/readline/include

all: $(NAME)

$(LIBFT):
	make -C libft

$(NAME): $(LIBFT) $(OBJ)
	cc $(FLAGS) $(OBJ) $(LIBFT) $(C_FLAGS) $(O_FLAGS) -o $(NAME)

clean:
	rm -f $(OBJ)
	make clean -C libft

fclean: clean
	rm -f $(NAME) $(LIBFT)

%.o: %.c
	cc $(FLAGS) $(C_FLAGS) -c $< -o $@

re: fclean all


