# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: librahim <librahim@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/07 15:17:41 by librahim          #+#    #+#              #
#    Updated: 2025/01/07 15:34:38 by librahim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRCS	=	srcs/gnl/get_next_line.c \
			srcs/gnl/get_next_line_utils.c \
			srcs/init_cub/init_cub.c \
			srcs/utils/tools.c \
			srcs/cub3d.c

H	=	cub3d.h


OBJS	=	$(SRCS:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror

MLXFLAGS = -lmlx -framework OpenGL -framework AppKit


%.o: %.c $(H)
	$(CC) $(CFLAGS) -c $< -o $@


#%.o : %.c $(HEADER)
#	$(CC) $(FLAGS) -c $< -o $@


all: $(NAME)

$(NAME): $(OBJS) $(H)
	$(CC) $(OBJS) $(MLXFLAGS) -o $(NAME) 

clean:
	rm -rf $(OBJS)


fclean: clean
	rm -rf $(NAME)


re: fclean all


.PHONY: all clean fclean re
