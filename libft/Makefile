# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkaron <vkaron@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/23 17:12:18 by vkaron            #+#    #+#              #
#    Updated: 2020/01/11 22:13:43 by vkaron           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, clean, fclean, re

FLAGS = -Wall -Wextra -Werror

C_FILES = 	ft_strlen.c ft_strdup.c ft_strdup2.c ft_strndup.c ft_swap.c\
			ft_atoi.c ft_atoi_16.c ft_strrdup.c ft_strmcat.c ft_strfind.c\
			ft_isspace.c ft_strncpy.c ft_strsplit.c get_next_line.c\
			ft_itoa.c ft_pad_left.c ft_memcpy.c ft_putstr_fd.c ft_putstr.c\
			ft_strcmp.c ft_strcpy.c ft_strjoin.c ft_memalloc.c ft_memset.c\
			ft_putchar_fd.c ft_putnbr_fd.c ft_putchar.c
 
O_FILES = $(C_FILES:.c=.o)

H_DIR = -I./

NAME = libft.a

all: $(NAME)

$(NAME): $(O_FILES)
	ar rc $(NAME) $(O_FILES)

%.o: %.c libft.h
	gcc	$(FLAGS)  -c $< $(H_DIR)

clean:
	rm -f $(O_FILES)

fclean : clean
	rm -f $(NAME)

re: fclean all
