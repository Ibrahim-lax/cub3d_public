SRCS = $(wildcard get_next_line/*.c) $(wildcard srcs/*.c) $(wildcard srcs/utils/*.c) $(wildcard srcs/init_cub/*.c)
OBJD = obj
OBJS = $(patsubst %.c,$(OBJD)/%.o,$(SRCS))

NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror 
MLXFLAGS = -lmlx -framework OpenGL -framework AppKit

$(OBJD)/%.o: %.c includes/cub3d.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(MLXFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -rf $(OBJD)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re