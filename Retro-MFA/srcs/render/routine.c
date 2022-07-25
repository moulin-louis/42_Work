/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 16:00:34 by ldutriez          #+#    #+#             */
/*   Updated: 2022/07/24 13:05:18 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "retromfa.h"
#include <time.h>
#include <unistd.h>

static int key_press(int keycode, t_mlx *mlx)
{
	if (keycode == ESC)
		quit_mlx(mlx, EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

static int update(void *update_props[3])
{
	t_mlx *mlx = update_props[0];
	t_list bmp_file = update_props[1];
	t_int2 *max_size = update_props[2];
	t_list bmp_file_tmp;

	bmp_file_tmp = bmp_file;

	while (bmp_file_tmp)
	{
		draw_mfa_image(mlx, (t_b_data *)bmp_file_tmp->data, max_size);
		bmp_file_tmp = bmp_file_tmp->next;
	}
	draw_mfa_image(mlx, NULL, max_size);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
	sleep(1);
	return (EXIT_SUCCESS);
}

static int manage_close(t_mlx *mlx)
{
	quit_mlx(mlx, EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

void mlx_routine(t_mlx *mlx, t_list bmp_file, t_int2 *max_size)
{
	void *update_props[3];

	update_props[0] = mlx;
	update_props[1] = bmp_file;
	update_props[2] = max_size;
	mlx_loop_hook(mlx->mlx, update, update_props);
	mlx_hook(mlx->win, 2, 1L << 0, key_press, mlx);
	mlx_hook(mlx->win, 17, 1L << 17, manage_close, mlx);
	mlx_loop(mlx->mlx);
}