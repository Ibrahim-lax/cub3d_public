/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <mjuicha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 13:22:12 by mjuicha           #+#    #+#             */
/*   Updated: 2024/12/30 18:04:52 by mjuicha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define SUCCESS    1
# define FAILURE    0

# define ERROR_ARG "\033[31mError: Wrong number of arguments\n\033[0m"
# define ERROR_EXT "\033[31mError: Wrong extension\n\033[0m"
# define OPPEN_ERROR "\033[31mError: Can't open file\n\033[0m"
# include <unistd.h>
# include <stdio.h> 
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>

typedef struct s_game
{
    void    *mlx;
    void    *mlx_win;
    int     fd_map;
}               t_game;

/***********************  utils  ***********************/
size_t  ft_strlen(const char *str);
int     ft_strcmp(const char *s1, const char *s2);
void	ft_putendl_fd(char *str, int fd);
/***********************  init  ***********************/
t_game   *init_cub(int ac, char **av);

#endif