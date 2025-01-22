/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <mjuicha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 13:22:12 by mjuicha           #+#    #+#             */
/*   Updated: 2025/01/22 09:34:35 by mjuicha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/***********************  includes  ***********************/
#ifndef CUB3D_H
# define CUB3D_H
/***********************  defines  ************************/
# define SUCCESS    1
# define FAILURE    0
/***********************  window  *************************/
# define WIDTH      480
# define HEIGHT     480
/***********************  keys  ***************************/
# define ESC        53
# define W          13
# define S          1
# define A          0
# define D          2
# define LEFT       123
# define RIGHT      124
/***********************  movement  ***********************/
# define MS         4
# define CTE        5
# define ANGLE      10
/***********************  colors  *************************/
# define BLACK      0x00000000
# define WHITE      0x00FFFFFF
# define YELLOW     0x00FFFF00
/***********************  errors  *************************/
# define ERROR_ARG "\033[31mError: Wrong number of arguments\n\033[0m"
# define ERROR_EXT "\033[31mError: Wrong extension\n\033[0m"
# define OPPEN_ERROR "\033[31mError: Can't open file\n\033[0m"
/***********************  includes  ***********************/
# include <unistd.h>
# include <stdio.h> 
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include "get_next_line.h"
/***********************  structures  *********************/
typedef struct s_map
{
    char        *line;
    struct s_map *next;
}               t_map;

typedef struct s_info
{
    int     height;
    int     width;
}               t_info;

typedef struct s_player
{
    float     player_x;
    float     player_y;
    int       px_x;
    int       px_y;
}               t_player;


typedef struct s_game
{
    void    *mlx;
    void    *mlx_win;
    void    *img;
    
    char    **map;
    
    t_info  *info;
    t_player *player;
    
    int     width;
    int     height;
    int     mapfd;
    double   angle;
    int fake;
}               t_game;

/***********************  utils  ***********************/
size_t  ft_strlen(const char *str);
int     ft_strcmp(const char *s1, const char *s2);
void	ft_putendl_fd(char *str, int fd);
char	*ft_strdup(const char *s1);
/***********************  init  ***********************/
t_game   *init_cub(int ac, char **av);
/***********************  draw  ***********************/
void	draw_walls(t_game *game);
void	player(t_game *game);
#endif