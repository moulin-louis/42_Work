/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 15:36:28 by loumouli          #+#    #+#             */
/*   Updated: 2022/06/18 13:01:18 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../lib/mlx_linux/mlx.h"
# include "../lib/libft/libft.h"
# include "../lib/ft_printf/inc/ft_printf.h"
# include <X11/X.h>
# include <math.h>
# include <X11/keysym.h>
# include <stdio.h>
# include <sys/stat.h>
# include <fcntl.h>
# define PATH_PLAYER "./asset/player.xpm"
# define PATH_BACK "./asset/back.xpm"
# define PATH_WALL "./asset/wall.xpm"
# define PATH_COLL "./asset/coll.xpm"
# define PATH_EXIT "./asset/exit.xpm"

typedef struct s_data
{
	void	*init;
	void	*window;
	void	*background;
	void	*player;
	void	*wall;
	void	*coll;
	void	*exit;

	char	**map;

	int		counter;
	int		nbr_coll;
	int		pos_x;
	int		pos_y;
	int		height;
	int		width;
}	t_data;

int		render(t_data *data);
int		update_frame(t_data *data);
int		close_window(t_data *data);
void	push_map(t_data *data);

void	setup_hook(t_data *data);

int		setup_map(t_data *data, char *path);

int		setup_init(t_data *data);
void	nullify_void_ptr(t_data *data);

void	destroy_double_array(t_data *data);
int		destroy_anything(t_data *data);

void	move_up(t_data *data, int i, int j);
void	move_down(t_data *data, int i, int j);
void	move_left(t_data *data, int i, int j);
void	move_right(t_data *data, int i, int j);

#endif
