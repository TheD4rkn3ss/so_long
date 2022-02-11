/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucferna <lucferna@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 13:54:24 by lucferna          #+#    #+#             */
/*   Updated: 2022/02/09 14:18:26 by lucferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	ft_close(t_program *game)
{
	printf("Bye\n");
	mlx_destroy_image(game->mlx, game->coin.ptr);
	mlx_destroy_image(game->mlx, game->ground.ptr);
	mlx_destroy_image(game->mlx, game->exit.ptr);
	mlx_destroy_image(game->mlx, game->player.ptr);
	mlx_destroy_image(game->mlx, game->wall.ptr);
	mlx_destroy_window(game->mlx, game->window);
	mlx_destroy_display(game->mlx);
	free(game->str);
	free(game->mlx);
	exit(0);
	return (0);
}

int	can_move(t_program *game, char *str, char key)
{
	size_t	i;
	int		x;
	int		y;

	i = 0;
	x = (game->player_pos.x / 63);
	y = (game->player_pos.y / 63);
	if (key == 'D')
		i = ((game->window_size_x + 1) * y) + (x + 1);
	if (key == 'S')
		i = ((game->window_size_x + 1) * (y + 1)) + x;
	if (key == 'A')
		i = ((game->window_size_x + 1) * y) + (x - 1);
	if (key == 'W')
		i = ((game->window_size_x + 1) * (y - 1)) + x;
	if (str[i] == 'C')
	{
		game->items -= 1;
		str[i] = '0';
	}
	if (game->items <= 0 && str[i] == 'E')
		return (printf("You won! ") && ft_close(game));
	if (str[i] != '1' && str[i] != 'E')
		return (1);
	return (0);
}

int	move_player(int key, t_program *game)
{
	if (key == 100 || key == RIGHT)
	{
		refresh_str(game, 'D');
		game->player_pos.x += 63;
	}
	else if (key == 97 || key == LEFT)
	{
		refresh_str(game, 'A');
		game->player_pos.x -= 63;
	}
	else if (key == 115 || key == DOWN)
	{
		refresh_str(game, 'S');
		game->player_pos.y += 63;
	}
	else if (key == 119 || key == UP)
	{
		refresh_str(game, 'W');
		game->player_pos.y -= 63;
	}
	game->moves += 1;
	printf("Number of moves: %lu\n", game->moves);
	return (0);
}

int	ft_input(int key, t_program *game)
{
	mlx_put_image_to_window(game->mlx, game->window, game->ground.ptr,
		game->player_pos.x, game->player_pos.y);
	if ((key == 100 || key == 65363)
		&& can_move(game, game->str, 'D') != 0)
		move_player(key, game);
	else if ((key == 97 || key == 65361)
		&& can_move(game, game->str, 'A') != 0)
		move_player(key, game);
	else if ((key == 115 || key == 65364)
		&& can_move(game, game->str, 'S') != 0)
		move_player(key, game);
	else if ((key == 119 || key == 65362)
		&& can_move(game, game->str, 'W') != 0)
		move_player(key, game);
	else if (key == 65307)
		ft_close(game);
	mlx_put_image_to_window(game->mlx, game->window, game->player.ptr,
		game->player_pos.x, game->player_pos.y);
	return (0);
}

t_image	ft_new_image(void *mlx, char *path)
{
	t_image	img;

	img.ptr = mlx_xpm_file_to_image(mlx, path, &img.size.x, &img.size.y);
	img.pixels = mlx_get_data_addr(img.ptr, &img.bits, &img.line_size,
			&img.endian);
	return (img);
}
