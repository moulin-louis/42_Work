/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 17:24:56 by loumouli          #+#    #+#             */
/*   Updated: 2022/06/21 15:24:25 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	*fct(void *init, char *path, int *x, int *y)
{
	return (mlx_xpm_file_to_image(init, path, x, y));
}

int	ft_load_img(t_data *data)
{
	int	n;

	data->background = fct(data->init, PATH_BACK, &n, &n);
	data->wall = fct(data->init, PATH_WALL, &n, &n);
	data->player.img_0 = fct(data->init, "./asset/char/char_0.xpm", &n, &n);
	data->player.img_1 = fct(data->init, "./asset/char/char_1.xpm", &n, &n);
	data->player.img_2 = fct(data->init, "./asset/char/char_2.xpm", &n, &n);
	data->player.img_3 = fct(data->init, "./asset/char/char_3.xpm", &n, &n);
	data->player.img_4 = fct(data->init, "./asset/char/char_4.xpm", &n, &n);
	data->player.img_5 = fct(data->init, "./asset/char/char_5.xpm", &n, &n);
	data->player.img_6 = fct(data->init, "./asset/char/char_6.xpm", &n, &n);
	data->player.img_7 = fct(data->init, "./asset/char/char_7.xpm", &n, &n);
	data->coll = fct(data->init, PATH_COLL, &n, &n);
	data->exit = fct(data->init, PATH_EXIT, &n, &n);
	if (data->background == NULL || data->wall == NULL || data->player.img_0
		== NULL || data->player.img_1 == NULL || data->player.img_2 == NULL
		|| data->player.img_3 == NULL || data->player.img_4 == NULL
		|| data->player.img_5 == NULL || data->player.img_6 == NULL
		|| data->player.img_7 == NULL)
		return (ft_printf("Error\nFailed to load a image\n"), 0);
	if (data->coll == NULL || data->exit == NULL)
		return (ft_printf("Error\nFailed to load a image\n"), 0);
	return (1);
}

int	setup_init(t_data *data)
{
	data->init = mlx_init();
	if (data->init == NULL)
		return (ft_printf("Error\nError mlx_init\n"), destroy_anything(data), 0);
	if (ft_load_img(data) == 0)
		return (destroy_anything(data), 0);
	data->window = mlx_new_window(data->init, data->width_windows,
			data->height_windows,
			"so_long");
	if (data->window == NULL)
		return (ft_printf("Error\nError mlx_new_windows\n"), 0);
	return (1);
}
