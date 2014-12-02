#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yfuks <yfuks@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/12/02 16:16:09 by yfuks             #+#    #+#              #
#    Updated: 2014/12/02 16:39:03 by yfuks            ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = fdf

SRC = 	sources/ft_fdf.c 			\
		sources/ft_fdf_map.c		\
		sources/ft_put_pixel.c		\
		sources/get_next_line.c		\
		sources/main.c				\
		libft/libft.a

HEAD = ./includes

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror

LIB = /usr/x11/lib -lmlx -lXext -lX11

all : $(NAME)

$(NAME):
	make ./libft
	gcc $(FLAGS) $(SRC) -I $(HEAD) -L $(LIB) -o $(NAME)

clean:
		make ./libft clean
		/bin/rm -f $(OBJ)

fclean: clean
		make ./libft fclean
		/bin/rm -f $(NAME)

re: fclean all