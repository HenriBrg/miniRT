# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: henri <henri@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/28 00:56:29 by henri             #+#    #+#              #
#    Updated: 2019/12/15 19:11:34 by henri            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

SRCS = srcs/main.c srcs/maths/vec1.c srcs/maths/vec2.c srcs/maths/vec3.c	   \
	   srcs/maths/trigo.c													   \
	   srcs/intersections/intersection.c srcs/intersections/spheres.c		   \
	   srcs/intersections/planes.c srcs/intersections/squares.c				   \
	   srcs/intersections/triangles.c srcs/parser/parser.c					   \
	   srcs/intersections/cylinders.c

OBJS = ${SRCS:.c=.o}

FLAGS = -Wall -Wextra -Werror

DEBUG = 1

# ifndef VERBOSE
# .SILENT:
# endif

all: $(NAME)

run: all
	./miniRT

debug: $(OBJS)
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
