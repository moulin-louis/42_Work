/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 15:36:28 by loumouli          #+#    #+#             */
/*   Updated: 2022/06/15 14:33:01 by loumouli         ###   ########.fr       */
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
# define PATH_MAP "./map/basic.ber"
# define PATH_CHAR "./asset/character.xpm"
# define PATH_BACK "./asset/background.xpm"

typedef struct s_char
{
	void	*char_ptr;
	int		pos_x;
	int		pos_y;
	int		width_char;
	int		height_char;

}	t_char;

typedef struct s_background
{
	void	*back_ptr;
	int		width_back;
	int		height_back;
}	t_back;

typedef struct s_data
{
	void	*init;
	void	*window;
	t_back	background;
	t_char	character;
	char	**map;

	int		counter;
}	t_data;

int		render(t_data *data);
int		update_frame(t_data *data);
int		close_window(t_data *data);

void	setup_hook(t_data *data);

int		setup_map(t_data *data);

void	destroy_double_array(t_data *data);

#endif
