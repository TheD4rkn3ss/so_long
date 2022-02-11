/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucferna <lucferna@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 01:14:14 by lucferna          #+#    #+#             */
/*   Updated: 2022/02/09 14:18:33 by lucferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (*s++)
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	char	*new;
	size_t	size;
	int		i;

	i = 0;
	size = ft_strlen(s) + 1;
	new = malloc(size * sizeof(char));
	if (new)
	{
		while (s[i])
		{
			new[i] = s[i];
			i++;
		}
		new[i] = '\0';
		return (new);
	}
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	char	*start;

	if (!s1 || !s2)
		return (NULL);
	new = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (new == NULL)
		return (NULL);
	start = new;
	while (*s1)
		*new++ = *s1++;
	while (*s2)
		*new++ = *s2++;
	*new = '\0';
	return (start);
}

int	map_reader(t_program *game, int fd)
{
	char	*buffer;
	char	*hold;
	int		n_read;

	if (fd <= 0)
		return (-1);
	buffer = malloc(2 * sizeof(char));
	game->str = ft_strdup("");
	n_read = 1;
	while (n_read)
	{
		n_read = read(fd, buffer, 1);
		if (n_read == -1)
			return (-1);
		buffer[n_read] = '\0';
		hold = game->str;
		game->str = ft_strjoin(game->str, buffer);
		free(hold);
	}
	free(buffer);
	close(fd);
	return (1);
}

void	map_maker(char c, t_program *game)
{
	if (c == '1')
		mlx_put_image_to_window(game->mlx, game->window, game->wall.ptr,
			game->screen_pos.x, game->screen_pos.y);
	else if (c == '0' || (game->player_pos.x != 0 && c == 'P'))
		mlx_put_image_to_window(game->mlx, game->window, game->ground.ptr,
			game->screen_pos.x, game->screen_pos.y);
	else if (c == 'P')
	{
		game->player_pos.x = game->screen_pos.x;
		game->player_pos.y = game->screen_pos.y;
	}
	else if (c == 'E')
		mlx_put_image_to_window(game->mlx, game->window, game->exit.ptr,
			game->screen_pos.x, game->screen_pos.y);
	else if (c == 'C')
		mlx_put_image_to_window(game->mlx, game->window, game->coin.ptr,
			game->screen_pos.x, game->screen_pos.y);
	if (c == '\n')
	{
		game->screen_pos.y += 63;
		game->screen_pos.x = 0;
	}
	else
		game->screen_pos.x += 63;
}
