/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 15:49:03 by ldutriez          #+#    #+#             */
/*   Updated: 2022/07/23 16:14:33 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "retromfa.h"
#include <strings.h> //? Needed by bzero

t_mlx init_mlx(char window_name[10])
{
	t_mlx mlx;

	mlx.mlx = mlx_init();
	if (mlx.mlx == NULL)
	{
		dprintf(2, "Error\nUnable to init mlx\n");
		exit(1);
	}
	mlx.win = mlx_new_window(mlx.mlx, W_WIDTH, W_HEIGHT, window_name);
	if (mlx.win == NULL)
	{
		dprintf(2, "Error\nUnable to create a window\n");
		exit(1);
	}
	bzero((void *)&mlx.img, sizeof(t_img));
	mlx.img.img = mlx_new_image(mlx.mlx, W_WIDTH, W_HEIGHT);
	mlx.img.addr = mlx_get_data_addr(mlx.img.img, &mlx.img.bits_pxl,
									 &mlx.img.line_len, &mlx.img.endian);
	return (mlx);
}