/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 17:24:56 by loumouli          #+#    #+#             */
/*   Updated: 2022/06/27 12:21:59 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	*fct(void *init, char *path, int *x, int *y)
{
	return (mlx_xpm_file_to_image(init, path, x, y));
}

int	load_nbr(t_data *data)
{
	int	n;

	data->nbr.zero = fct(data->init, "./asset/nbr/zero.xpm", &n, &n);
	data->nbr.one = fct(data->init, "./asset/nbr/one.xpm", &n, &n);
	data->nbr.two = fct(data->init, "./asset/nbr/two.xpm", &n, &n);
	data->nbr.three = fct(data->init, "./asset/nbr/three.xpm", &n, &n);
	data->nbr.four = fct(data->init, "./asset/nbr/four.xpm", &n, &n);
	data->nbr.five = fct(data->init, "./asset/nbr/five.xpm", &n, &n);
	data->nbr.six = fct(data->init, "./asset/nbr/six.xpm", &n, &n);
	data->nbr.seven = fct(data->init, "./asset/nbr/seven.xpm", &n, &n);
	data->nbr.eight = fct(data->init, "./asset/nbr/eight.xpm", &n, &n);
	data->nbr.nine = fct(data->init, "./asset/nbr/nine.xpm", &n, &n);
	if (data->nbr.zero == NULL || data->nbr.one == NULL || data->nbr.two == NULL
		|| data->nbr.three == NULL || data->nbr.four == NULL ||
		data->nbr.five == NULL || data->nbr.six == NULL || data->nbr.seven == NULL
		|| data->nbr.eight == NULL || data->nbr.nine == NULL)
		return (0);
	return (1);
}

int	ft_load_img(t_data *data)
{
	int	n;

	data->background = fct(data->init, PATH_BACK, &n, &n);
	data->wall = fct(data->init, PATH_WALL, &n, &n);
	data->coll = fct(data->init, PATH_COLL, &n, &n);
	data->exit = fct(data->init, PATH_EXIT, &n, &n);
	data->enemies = fct(data->init, PATH_ENEMIES, &n, &n);
	data->player.img_0 = fct(data->init, "./asset/char/char_0.xpm", &n, &n);
	data->player.img_1 = fct(data->init, "./asset/char/char_1.xpm", &n, &n);
	data->player.img_2 = fct(data->init, "./asset/char/char_2.xpm", &n, &n);
	data->player.img_3 = fct(data->init, "./asset/char/char_3.xpm", &n, &n);
	data->player.img_4 = fct(data->init, "./asset/char/char_4.xpm", &n, &n);
	data->player.img_5 = fct(data->init, "./asset/char/char_5.xpm", &n, &n);
	data->player.img_6 = fct(data->init, "./asset/char/char_6.xpm", &n, &n);
	data->player.img_7 = fct(data->init, "./asset/char/char_7.xpm", &n, &n);
	if (data->background == NULL || data->wall == NULL || data->player.img_0
		== NULL || data->player.img_1 == NULL || data->player.img_2 == NULL
		|| data->player.img_3 == NULL || data->player.img_4 == NULL
		|| data->player.img_5 == NULL || data->player.img_6 == NULL
		|| data->player.img_7 == NULL)
		return (ft_printf("Error\nFailed to load a image\n"), 0);
	if (data->coll == NULL || data->exit == NULL || load_nbr(data) == 0)
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
