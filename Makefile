# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: henri <henri@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/28 00:56:29 by henri             #+#    #+#              #
#    Updated: 2019/11/20 14:40:10 by hberger          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

SRCS = srcs/main.c

OBJS = ${SRCS:.c=.o}

FLAGS = -Wall -Wextra -Werror

# ifndef VERBOSE
# .SILENT:
# endif

all: $(NAME)

run: all
	./miniRT

.c.o:
	gcc $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	gcc $(FLAGS) $(SRCS) -o $(NAME) -L. lib/libft.a -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

# Compilation with minilibx :
# gcc -I /usr/local/include main.c -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit
