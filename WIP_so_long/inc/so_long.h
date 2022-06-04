/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 15:36:28 by loumouli          #+#    #+#             */
/*   Updated: 2022/06/04 15:57:34 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
#define SO_LONG_H

#include "../mlx_linux/mlx.h"
#include "../mlx_linux/mlx_int.h"
#include "../libft/libft.h"
#include "../ft_printf/inc/ft_printf.h"
#include <X11/X.h>
#include <math.h>
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

typedef struct s_data
{
	void	*init;
	void	*window;
	int		counter;
}	t_data;

#endif
