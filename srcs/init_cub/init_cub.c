/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <mjuicha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 13:34:45 by mjuicha           #+#    #+#             */
/*   Updated: 2024/12/30 18:05:50 by mjuicha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
	if (!game)
		return (FAILURE);
	return (SUCCESS);
}

t_game	*start_game(t_game *game)
{
	game->mlx = mlx_init();
	game->mlx_win = mlx_new_window(game->mlx, 1920, 1080, "cub3D");
	
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
	game->fd_map = fd;
	if (!valid_format(game))
		return (NULL);
	game = start_game(game);
	return (game);
}
