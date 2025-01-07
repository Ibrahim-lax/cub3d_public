/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: librahim <librahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 13:22:12 by mjuicha           #+#    #+#             */
/*   Updated: 2025/01/07 15:41:43 by librahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define SUCCESS    1
# define FAILURE    0

# define WIDTH      480
# define HEIGHT     320

# define ERROR_ARG "\033[31mError: Wrong number of arguments\033[0m"
# define ERROR_EXT "\033[31mError: Wrong extension\033[0m"
# define OPPEN_ERROR "\033[31mError: Can't open file\033[0m"
# include <unistd.h>
# include <stdio.h> 
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif


/************************** STUCTS ***************************/

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

typedef struct s_game
{
    void    *mlx;
    void    *mlx_win;
    char    **map;
    t_info  *info;
    int     width;
    int     height;
    int     mapfd;
}               t_game;

/************************** GNL ***************************/

char	*get_next_line(int fd);
char	*empty_str(void);
char	*ft_strchr(const char *str, int c);
char	*ft_strjoin(char *str, char *buff);
char	*the_line(char *str);
char	*next_line(char *str);
char	*read_line(int fd, char *str);

/***********************  utils  ***********************/

size_t  ft_strlen(char *str);
int     ft_strcmp(const char *s1, const char *s2);
void	ft_putendl_fd(char *str, int fd);
char	*ft_strdup(const char *s1);

/***********************  init  ***********************/

t_game   *init_cub(int ac, char **av);

#endif