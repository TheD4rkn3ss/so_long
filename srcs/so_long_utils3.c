/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucferna <lucferna@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 21:51:31 by lucferna          #+#    #+#             */
/*   Updated: 2022/02/09 14:18:36 by lucferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	map_check(t_program *game)
{
	game->window_size_x = 0;
	game->window_size_y = 0;
	if (map_error_one(game, game->str) != 1
		|| check_walls(game, game->str) != 1 || check_pec(game, game->str) != 1)
		return (-1);
	return (1);
}

int	map_error_one(t_program *game, char *str)
{
	size_t	i;
	int		trigger;

	i = 0;
	trigger = 1;
	while (str[i] != '\0')
	{
		if (str[i] != '1' && str[i] != '0' && str[i] != 'P' && str[i] != 'E'
			&& str[i] != 'C' && str[i] != '\n')
			return (-1);
		if (str[i] == '\n')
			game->window_size_y += 1;
		i++;
	}
	i = 0;
	while (str[i])
	{
		if (str[i++] == '\n')
			trigger = 0;
		if (trigger != 0)
			game->window_size_x += 1;
	}
	if (game->window_size_y < 3 || game->window_size_x < 3)
		return (-1);
	return (1);
}

int	check_roll(t_program *game, char *str, size_t i)
{
	int	x;
	int	y;

	x = game->window_size_x;
	y = game->window_size_y - 2;
	while (y != 0)
	{
		while (x != 0)
		{
			if (str[i] == '\0')
				return (0);
			if (str[i + 1] == '\n' && (str[i] != '1' || str[i + 2] != '1'))
				return (0);
			if (str[i++] == '\n')
				break ;
			x--;
		}
		if (x != 0)
			return (0);
		else
			x = game->window_size_x;
		y--;
		i++;
	}
	return (i);
}

int	check_walls(t_program *game, char *str)
{
	size_t	i;
	int		x;

	i = 0;
	x = game->window_size_x;
	while (i != game->window_size_x)
	{
		if (str[i++] != '1')
			return (-1);
	}
	i = check_roll(game, str, i + 1);
	if (i == 0)
		return (-1);
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			break ;
		else if (str[i++] != '1')
			return (-1);
		x--;
	}
	if (x != 0)
		return (-1);
	return (1);
}

int	check_pec(t_program *game, char *str)
{
	int		count[3];
	size_t	i;

	i = 0;
	game->items = 0;
	count[0] = 0;
	count[1] = 0;
	count[2] = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 'P')
			count[0] = 1;
		else if (str[i] == 'E')
			count[1] = 1;
		else if (str[i] == 'C')
		{
			count[2] = 1;
			game->items++;
		}
		i++;
	}
	if (count[0] != 1 || count[1] != 1 || count[2] != 1)
		return (-1);
	return (1);
}
