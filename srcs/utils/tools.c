/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: librahim <librahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 15:29:30 by mjuicha           #+#    #+#             */
/*   Updated: 2025/01/07 15:34:09 by librahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

size_t	ft_strlen(char *str)
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

char	*ft_strdup(const char *s1)
{
	size_t	x;
	size_t	i;
	char	*dest;

	x = 0;
	while (s1[x])
		x++;
	x++;
	dest = (char *)malloc(sizeof(char) * x);
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	ft_putendl_fd(char *str, int fd)
{
	if (fd == -1 || !str)
		return ;
	write(fd, str, ft_strlen(str));
	write(fd, "\n", 1);
}
