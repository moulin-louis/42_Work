/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 15:36:28 by loumouli          #+#    #+#             */
/*   Updated: 2022/06/27 12:32:57 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include "../lib/mlx_linux/mlx.h"
# include "../lib/libft/libft.h"
# include "../lib/ft_printf/inc/ft_printf.h"
# include <X11/X.h>
# include <math.h>
# include <X11/keysym.h>
# include <stdio.h>
# include <sys/stat.h>
# include <fcntl.h>
# define PATH_BACK "./asset/back.xpm"
# define PATH_WALL "./asset/wall.xpm"
# define PATH_COLL "./asset/coll.xpm"
# define PATH_EXIT "./asset/exit.xpm"
# define PATH_ENEMIES "./asset/enemies.xpm"

typedef struct s_char
{
	void	*img_0;
	void	*img_1;
	void	*img_2;
	void	*img_3;
	void	*img_4;
	void	*img_5;
	void	*img_6;
	void	*img_7;
}	t_char;

typedef struct s_nbr
{
	void	*zero;
	void	*one;
	void	*two;
	void	*three;
	void	*four;
	void	*five;
	void	*six;
	void	*seven;
	void	*eight;
	void	*nine;
}	t_nbr;

typedef struct s_data
{
	void	*init;
	void	*window;
	void	*background;
	void	*wall;
	void	*coll;
	void	*exit;
	void	*enemies;
	t_char	player;
	t_nbr	nbr;

	char	**map;

	int		counter;
	int		ctr_anim;
	int		nbr_coll;
	int		height_windows;
	int		width_windows;
	int		pos_x;
	int		pos_y;
}	t_data;

int		render(t_data *data);
int		update_frame(t_data *data);
int		close_window(t_data *data, int win);
void	push_map(t_data *data);

void	setup_hook(t_data *data);

int		setup_map(t_data *data, char *path);

void	display_score(t_data *data);

int		setup_init(t_data *data);

void	destroy_double_array(t_data *data);
int		destroy_anything(t_data *data);

void	move_up(t_data *data, int i, int j);
void	move_down(t_data *data, int i, int j);
void	move_left(t_data *data, int i, int j);
void	move_right(t_data *data, int i, int j);

#endif
