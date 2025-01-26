/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <mjuicha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 13:34:45 by mjuicha           #+#    #+#             */
/*   Updated: 2025/01/26 03:18:24 by mjuicha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_error(char *error)
{
	ft_putendl_fd(error, STDERR_FILENO);
}

int valid_args(int ac)
{
	if (ac == 2)
		return (SUCCESS);
	ft_error(ERROR_ARG);
	return (FAILURE);
}

int	valid_extension(char **av)
{
	if (!av || !av[1])
	{
		ft_error(ERROR_EXT);
		return (FAILURE);
	}
	if (ft_strcmp(".cub", &av[1][ft_strlen(av[1]) - 4]) != 0)
	{
		ft_error(ERROR_EXT);
		return (FAILURE);
	}
	return (SUCCESS);
}

int valid_input(int ac, char **av)
{
	if (!valid_args(ac))
		return (FAILURE);
	if (!valid_extension(av))
		return (FAILURE);
	return (SUCCESS);
}

int	valid_file(char **av)
{
	int	fd;

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		ft_error(OPPEN_ERROR);
	return (fd);
}

int	valid_format(t_game *game)
{
	(void)game;
	return (SUCCESS);
}

t_map	*new_map(char *line)
{
	t_map *new;

	if (!line)
		return (NULL);
	new = malloc(sizeof(t_map));
	if (!new)
		return (NULL);
	new->line = ft_strdup(line);
	new->next = NULL;
	return (new);
}

t_map	*add_back_map(t_map *map, t_map *new_map)
{
	t_map	*tmp;

	if (!new_map)
		return (map);
	if (!map)
		return (new_map);
	tmp = map;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_map;
	return (map);
}

void	show_array(char **array)
{
	int i = 0;
	while (array[i])
	{
		printf("array is %d  : %s",i , array[i]);
		i++;
	}
}
void	show_map(t_map *map)
{
	t_map *tmp = map;
	while (tmp)
	{
		if (tmp->line)
			printf("the line is : %s",tmp->line);
		tmp = tmp->next;
	}
	printf("\n");
}

int	mapcounter(t_map *map)
{
	t_map	*tmp;
	int		counter;

	counter = 0;
	tmp = map;
	while (tmp)
	{
		counter++;
		tmp = tmp->next;
	}
	return (counter);
}

char	**list2array(t_map *map)
{
	char	**array;
	int		i;
	int		counter;
	t_map	*tmp;

	counter = mapcounter(map);
	array = malloc(sizeof(char *) * (counter + 1));
	if (!array)
		return (NULL);
	i = 0;
	while (map && i < counter)
	{
		array[i] = ft_strdup(map->line);
		free(map->line);
		tmp = map;
		map = map->next;
		free(tmp);
		i++;
	}
	array[i] = NULL;
	return (array);
}

t_game	*get_map(t_game *game)
{
	t_map	*map = NULL;
	char	*str;

	str = get_next_line(game->mapfd);
	map = add_back_map(map, new_map(str));
	while (str)
	{
		free(str);
		str = get_next_line(game->mapfd);
		map = add_back_map(map, new_map(str));
	}
	game->map = list2array(map);
	close(game->mapfd);
	return (game);
}

t_info	*get_hw(t_game *game)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	if (!info)
		return (NULL);
	info->height = HEIGHT / game->height;
	info->width = WIDTH / game->width;
	printf("hw is %d and %d\n", info->height, info->width);
	return (info);
}

t_game	*get_info(t_game *game)
{
	int	i;

	i = 0;
	game->width = ft_strlen(game->map[0]) - 1;
	while (game->map[i])
		i++;
	game->height = i;
	game->info = get_hw(game);
	return (game);
}

int	close_window(t_game *game)
{
	mlx_destroy_window(game->mlx, game->mlx_win);
	printf("window closed\n");
	exit(0);
}

int	valid_position(t_game *game, int pos_x, int pos_y)
{
	(void)game;
	int px = pos_x / game->info->width;
	int py = pos_y / game->info->height;
	printf("px is %d and py is %d char is %c\n", px, py, game->map[py][px]);
	if (game->map[py][px] != '1')
	{
		printf("....x is %d and y is %d\n", pos_x, pos_y);
		if (game->map[(pos_y - CTE) / game->info->height][(pos_x - CTE) / game->info->width] != '1' &&
			game->map[(pos_y - CTE) / game->info->height][(pos_x + CTE) / game->info->width] != '1' &&
			game->map[(pos_y + CTE) / game->info->height][(pos_x - CTE) / game->info->width] != '1' &&
			game->map[(pos_y + CTE) / game->info->height][(pos_x + CTE) / game->info->width] != '1')
			return (1);
	}
	return (0);
}

int	check_wall(t_game *game, int keycode)
{
	int pos_x = game->player->px_x;
	int pos_y = game->player->px_y;

	if (keycode == W)
		pos_y -= MS;
	else if (keycode == S)
		pos_y += MS;
	else if (keycode == A)
		pos_x -= MS;
	else if (keycode == D)
		pos_x += MS;
	if (valid_position(game, pos_x, pos_y))
		return (1);
	return (0);
}

int	keys(int keycode, t_game *game)
{
	if (keycode == ESC)
		close_window(game);
	if (keycode == W && check_wall(game, keycode))
		game->player->px_y -= MS;
	else if (keycode == S && check_wall(game, keycode))
		game->player->px_y += MS;
	else if (keycode == A && check_wall(game, keycode))
		game->player->px_x -= MS;
	else if (keycode == D && check_wall(game, keycode))
		game->player->px_x += MS;
	else if (keycode == LEFT)
		game->angle -= ANGLE;
	else if (keycode == RIGHT)
		game->angle += ANGLE;
	mlx_clear_window(game->mlx, game->mlx_win);
	draw_walls(game);
	player(game);
	return (0);
}

long	get_time(void)
{
	struct timeval	time;
	long			c_time;

	gettimeofday(&time, NULL);
	c_time = time.tv_sec;
	return (c_time);
}

int mouse_hook(int button, t_game *game)
{
	(void)game;
	printf("button is %d\n", button);
	return (0);
}

void	events_hook(t_game *game)
{
	mlx_hook(game->mlx_win, 2, 0, keys, game);
	mlx_hook(game->mlx_win, 17, 0, close_window, game);
}

t_game	*get_player_pos(t_game *game)
{
	int i;
	int j;
	game->player = malloc(sizeof(t_player));
	if (!game->player)
		return (NULL);
	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] && game->map[i][j] == 'P')
			{
				game->player->player_x = j;
				game->player->player_y = i;
				game->player->px_x = j * game->info->width + (48 / 2);
				game->player->px_y = i * game->info->height + (48 / 2);
				break ;
			}
			j++;
		}
		i++;
	}
	return (game);
}

void	rectangle(int x, int y, t_game *game, void *img)
{
	mlx_put_image_to_window(game->mlx, game->mlx_win, img, x, y);
}


void	draw_walls(t_game *game)
{
	int i = 0, j = 0;
	int mx = 0, my = 0;
	while (i < HEIGHT)
	{
		j = 0;
		mx = 0;
		while (j < WIDTH)
		{
			if (game->map[my][mx] == '1')
				rectangle(j, i, game, game->black_block);
			else if (game->map[my][mx] == '0' || game->map[my][mx] == 'P')
				rectangle(j, i, game, game->white_block);
			j += game->info->width;
			mx++;
		}
		i += game->info->height;
		my++;
	}
}

void	pl(t_game *game)
{
	int x = game->player->px_x;
	printf("yo %d\n", x);
	int y = game->player->px_y;
	int maxx = x + CTE;
	int minx = x - CTE;
	int maxy = y + CTE;
	int miny = y - CTE;
	int i = miny;
	int j;
	while (i < maxy)
	{
		j = minx;
		while (j < maxx)
		{
			mlx_pixel_put(game->mlx, game->mlx_win, j, i, 0x00FF0000);
			j++;
		}
		i++;
	}
}

int	gx(int x, int y,int i, int j, double angle)
{
	if (angle == 0)
		return (j);
	return (round(x + (j - x) * cos(angle * M_PI / 180) - (i - y) * sin(angle * M_PI / 180)));
}

int	gy(int x, int y, int i, int j, double angle)
{
	if (angle == 0)
		return (i);
	return (round(y + (j - x) * sin(angle * M_PI / 180) + (i - y) * cos(angle * M_PI / 180)));
}

void	bresenhams_line(int x, int y, int endx, int endy, t_game *game)
{
	int dx = abs(endx - x);
	int dy = abs(endy - y);
	int sx = x < endx ? 1 : -1;
	int sy = y < endy ? 1 : -1;
	int err = dx - dy;
	int e2;

	while (1)
	{
		mlx_pixel_put(game->mlx, game->mlx_win, x, y, SKYBLUE);
		if (x == endx && y == endy)
			break ;
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y += sy;
		}
	}
}

// int	get_intersections(t_game *game, int x, int y)
// {}

void	sixty_angle(t_game *game)
{
	double angle = game->angle - 30;
	double max_angle = game->angle + 30;
	while (angle < max_angle)
	{
		cast_ray(game, angle);
		angle += 0.01;
	}
}

void cast_ray(t_game *game, double angle)
{
    double x = game->player->px_x;
    double y = game->player->px_y;
    double dx = cos(angle * M_PI / 180);
    double dy = sin(angle * M_PI / 180);
    int map_x, map_y;

    while (1)
    {
        x += dx;
        y += dy;
        map_x = (int)(x / game->info->width);
        map_y = (int)(y / game->info->height);
		if (map_x < 0 || map_y < 0 || map_x >= 10 || map_y >= 10)
            break;
        if (game->map[map_y][map_x] && game->map[map_y][map_x] == '1')
            break;
		if (game->map[map_y][map_x] == '0' || game->map[map_y][map_x] == 'P')
			mlx_pixel_put(game->mlx, game->mlx_win, (int)x, (int)y, BLUE);
	}
}


void	eye(t_game *game)
{
	sixty_angle(game);
	// cast_ray(game, 0);
}

void	player(t_game *game)
{
	pl(game);
	eye(game);
	// printf("angle is %f\n", game->angle);
}

t_game	*start_game(t_game *game)
{
	int aa, bb; 
	aa = 48;
	bb = 48;

	game = get_map(game);// clair
	game = get_info(game);// to remove
	game = get_player_pos(game);// clair
	game->angle = 0;
	game->mlx = mlx_init();
	game->mlx_win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub13d");
	game->white_block = mlx_xpm_file_to_image(game->mlx, "xpm_files/white.xpm", &aa, &bb);
	if (!game->white_block)
	{
		printf("error1\n");
		exit(0);
	}
	game->black_block = mlx_xpm_file_to_image(game->mlx, "xpm_files/black.xpm", &aa, &bb);
	if (!game->black_block)
	{
		printf("error\n");
		exit(0);
	}
	events_hook(game);
	game->fake = 0;
	draw_walls(game);
	player(game);
	mlx_loop(game->mlx);
	return (game);
}

t_game   *init_cub(int ac, char **av)
{
	t_game	*game;
	int		fd;

	if (!valid_input(ac, av))
		return (NULL);
	if ((fd = valid_file(av)) == -1)
		return (NULL);
	game = malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	game->mapfd = fd;
	if (!valid_format(game))
		return (NULL);
	game = start_game(game);
	return (game);
}
