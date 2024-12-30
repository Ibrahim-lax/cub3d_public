SRCS = 
SRCSBONUS =

OBJS = $(SRCS:.c=.o)
OBJSBONUS = $(SRCSBONUS:.c=.o)

NAME = cub3D
NAMEBONUS = cub3D_bonus

CC = gcc
CFLAGS = -Wall -Wextra -Werror
MLXFLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C mlx
	$(CC) $(CFLAGS) $(MLXFLAGS) -o $(NAME) $(OBJS)

bonus: $(NAMEBONUS)

$(NAMEBONUS): $(OBJSBONUS)
	$(MAKE) -C mlx
	$(CC) $(CFLAGS) $(MLXFLAGS) -o $(NAMEBONUS) $(OBJSBONUS)

clean:
	$(MAKE) -C mlx clean
	rm -f $(OBJS) $(OBJSBONUS)

fclean: clean
	$(MAKE) -C mlx clean
	rm -f $(NAME) $(NAMEBONUS)

re: fclean all

.PHONY: all bonus clean fclean re