/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <mjuicha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 15:29:30 by mjuicha           #+#    #+#             */
/*   Updated: 2024/12/30 18:04:46 by mjuicha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

size_t	ft_strlen(const char *str)
{
	int	x;

	x = 0;
    if (!str)
        return (x);
	while (str[x] != '\0')
		x++;
	return (x);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	x;

	x = 0;
    if (!s1 || !s2)
        return (x);
	while ((s1[x] || s2[x]) && s1[x] == s2[x])
		x++;
	return (s1[x] - s2[x]);
}
void	ft_putendl_fd(char *str, int fd)
{
	if (fd == -1 || !str)
		return ;
	write(fd, str, ft_strlen(str));
	write(fd, "\n", 1);
}
