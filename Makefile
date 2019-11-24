# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: henri <henri@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/28 00:56:29 by henri             #+#    #+#              #
#    Updated: 2019/11/24 23:01:57 by henri            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

SRCS = srcs/main.c srcs/vec.c srcs/color.c srcs/intersection.c

OBJS = ${SRCS:.c=.o}

FLAGS = -Wall -Wextra -Werror

DEBUG = 1
# ifndef VERBOSE
# .SILENT:
# endif

all: $(NAME)

run: all
	./miniRT

bug: $(OBJS)
	 gcc $(FLAGS) $(SRCS) -o $(NAME) -L. lib/libft.a -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit -D DEBUG=$(DEBUG)
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
