# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vmustone <vmustone@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/24 15:52:33 by vmustone          #+#    #+#              #
#    Updated: 2023/05/09 19:03:36 by vmustone         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FLAGS = -Wall -Werror -Wextra -I.

SRC := ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c\
		ft_isdigit.c ft_isprint.c ft_memchr.c ft_memcmp.c ft_memcpy.c\
	   	ft_memmove.c ft_memset.c ft_strchr.c ft_strcmp.c ft_strdup.c ft_strlcpy.c\
		ft_strlcat.c ft_strlen.c ft_strncmp.c ft_strnstr.c ft_strrchr.c\
		ft_tolower.c ft_toupper.c ft_putchar_fd.c ft_putstr_fd.c ft_putnbr_fd.c\
		ft_putendl_fd.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_strmapi.c ft_striteri.c\
		ft_split.c ft_itoa.c ft_putchar_val.c ft_putstr_val.c ft_putnbr_val.c\
		ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c\
		ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c\
		ft_lstmap_bonus.c ft_putchar_val.c ft_putnbr_val.c ft_putstr_val.c ft_printf.c ft_atof.c\
		ft_atoll.c

OBJ := $(SRC:.c=.o)

all: $(NAME)
$(NAME):
	cc -c $(FLAGS) $(SRC)
	ar rc $(NAME) $(OBJ)

clean:
	/bin/rm -f $(OBJ)

fclean:
	/bin/rm -f $(OBJ) $(NAME)

re: fclean all

.PHONY : all clean fclean re
