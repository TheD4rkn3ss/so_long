/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucferna <lucferna@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 01:10:24 by lucferna          #+#    #+#             */
/*   Updated: 2022/02/09 14:18:41 by lucferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	ft_start(t_program *game, int fd)
{
	int	i;

	i = 0;
	if (map_reader(game, fd) == -1 || map_check(game) == -1)
	{
		printf("Error\n");
		printf("Incorrect map file!\n");
		free(game->str);
		return (-1);
	}
	set_variables(game);
	while (game->str[i] != '\0')
		map_maker(game->str[i++], game);
	mlx_put_image_to_window(game->mlx, game->window, game->player.ptr,
		game->player_pos.x, game->player_pos.y);
	return (1);
}

void	set_variables(t_program *game)
{
	game->mlx = mlx_init();
	game->window = mlx_new_window(game->mlx, (game->window_size_x * 63),
			(game->window_size_y * 63), "so_long");
	game->player = ft_new_image(game->mlx, "./images/player.xpm");
	game->wall = ft_new_image(game->mlx, "./images/wall.xpm");
	game->ground = ft_new_image(game->mlx, "./images/ground.xpm");
	game->coin = ft_new_image(game->mlx, "./images/coin.xpm");
	game->exit = ft_new_image(game->mlx, "./images/exit.xpm");
	game->screen_pos.x = 0;
	game->screen_pos.y = 0;
	game->player_pos.x = 0;
	game->moves = 0;
}

int	refresh_str(t_program *game, int key)
{
	int	i;
	int	j;
	int	x;
	int	y;

	x = (game->player_pos.x / 63);
	y = (game->player_pos.y / 63);
	j = ((game->window_size_x + 1) * y) + x;
	if (key == 'D')
		i = ((game->window_size_x + 1) * y) + (x + 1);
	if (key == 'S')
		i = ((game->window_size_x + 1) * (y + 1)) + x;
	if (key == 'A')
		i = ((game->window_size_x + 1) * y) + (x - 1);
	if (key == 'W')
		i = ((game->window_size_x + 1) * (y - 1)) + x;
	game->str[i] = 'P';
	game->str[j] = '0';
	return (1);
}

int	refresh_screen(t_program *game)
{
	int	i;
	int	x;
	int	y;

	x = (game->player_pos.x / 63);
	y = (game->player_pos.y / 63);
	i = ((game->window_size_x + 1) * y) + x;
	game->str[i] = 'P';
	i = 0;
	mlx_clear_window(game->mlx, game->window);
	game->screen_pos.x = 0;
	game->screen_pos.y = 0;
	while (game->str[i] != '\0')
		map_maker(game->str[i++], game);
	mlx_put_image_to_window(game->mlx, game->window, game->player.ptr,
		game->player_pos.x, game->player_pos.y);
	return (0);
}

int	so_long(int fd)
{
	t_program	game;

	if (ft_start(&game, fd) == -1)
		return (printf("Bye!\n"));
	mlx_key_hook(game.window, ft_input, &game);
	mlx_hook(game.window, 17, 0, ft_close, &game);
	mlx_expose_hook(game.window, refresh_screen, &game);
	mlx_loop(game.mlx);
	return (1);
}
