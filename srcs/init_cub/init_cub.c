/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <mjuicha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 13:34:45 by mjuicha           #+#    #+#             */
/*   Updated: 2025/01/01 19:17:04 by mjuicha          ###   ########.fr       */
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
	// show_map(map);
	game->map = list2array(map);
	// show_array(game->map);
	close(game->mapfd);
	return (game);
}

t_info	*get_hw(t_game *game)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	if (!info)
		return (NULL);
	printf("game->height is %d\n", game->height);
	printf("game->width is %d\n", game->width);
	info->height = HEIGHT / game->height;
	info->width = WIDTH / game->width;
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
	printf("height is %d\n", game->info->height);
	printf("width is %d\n", game->info->width);
	return (game);
}

t_game	*start_game(t_game *game)
{
	game = get_map(game);
	game = get_info(game);
	game->mlx = mlx_init();
	game->mlx_win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3d");
	
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
