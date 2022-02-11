/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucferna <lucferna@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 13:48:55 by lucferna          #+#    #+#             */
/*   Updated: 2022/02/07 21:50:42 by lucferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

# define UP 65362
# define DOWN 65364
# define LEFT 65361
# define RIGHT 65363

typedef struct s_vector {
	int	x;
	int	y;
}				t_vector;

typedef struct s_image {
	void		*ptr;
	t_vector	size;
	char		*pixels;
	int			bits;
	int			line_size;
	int			endian;
}				t_image;

typedef struct s_program {
	void			*mlx;
	char			*str;
	size_t			items;
	size_t			moves;
	size_t			window_size_x;
	size_t			window_size_y;
	void			*window;
	t_image			player;
	t_image			coin;
	t_image			wall;
	t_image			ground;
	t_image			exit;
	t_vector		player_pos;
	t_vector		screen_pos;
}				t_program;

int			can_move(t_program *game, char *str, char key);
int			check_pec(t_program *game, char *str);
int			check_roll(t_program *game, char *str, size_t i);
int			check_walls(t_program *game, char *str);
int			ft_close(t_program *game);
int			ft_input(int key, t_program *game);
t_image		ft_new_image(void *mlx, char *path);
char		*ft_strdup(const char *s);
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlen(const char *s);
int			map_check(t_program *game);
int			map_error_one(t_program *game, char *str);
void		map_maker(char c, t_program *game);
int			map_reader(t_program *game, int fd);
int			move_player(int key, t_program *game);
int			refresh_screen(t_program *game);
int			refresh_str(t_program *game, int key);
void		set_variables(t_program *game);
int			so_long(int fd);

#endif
