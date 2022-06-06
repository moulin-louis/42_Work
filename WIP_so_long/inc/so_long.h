/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 15:36:28 by loumouli          #+#    #+#             */
/*   Updated: 2022/06/06 17:58:26 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
#define SO_LONG_H

#include "../mlx_linux/mlx.h"
#include "../libft/libft.h"
#include "../ft_printf/inc/ft_printf.h"
#include <X11/X.h>
#include <math.h>
#include <X11/keysym.h>
#define WINDOW_WIDTH 1980
#define WINDOW_HEIGHT 1080


typedef struct s_data
{
	void	*init;
	void	*window;
	void	*background;
	void	*character;

	int		position_char_x;
	int		position_char_y;
	int		width_img_1;
	int		counter;
	int		height_img_1;

}	t_data;



#endif
