/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 17:24:56 by loumouli          #+#    #+#             */
/*   Updated: 2022/07/25 15:31:25 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/so_long_bonus.h"

void	*fct(void *init, char *path)
{
	int	n;

	return (mlx_xpm_file_to_image(init, path, &n, &n));
}

int	load_nbr(t_data *data)
{
	data->nbr.zero = fct(data->init, "./asset/nbr/zero.xpm");
	data->nbr.one = fct(data->init, "./asset/nbr/one.xpm");
	data->nbr.two = fct(data->init, "./asset/nbr/two.xpm");
	data->nbr.three = fct(data->init, "./asset/nbr/three.xpm");
	data->nbr.four = fct(data->init, "./asset/nbr/four.xpm");
	data->nbr.five = fct(data->init, "./asset/nbr/five.xpm");
	data->nbr.six = fct(data->init, "./asset/nbr/six.xpm");
	data->nbr.seven = fct(data->init, "./asset/nbr/seven.xpm");
	data->nbr.eight = fct(data->init, "./asset/nbr/eight.xpm");
	data->nbr.nine = fct(data->init, "./asset/nbr/nine.xpm");
	if (data->nbr.zero == NULL || data->nbr.one == NULL || data->nbr.two == NULL
		|| data->nbr.three == NULL || data->nbr.four == NULL
		|| data->nbr.five == NULL || data->nbr.six == NULL
		|| data->nbr.seven == NULL
		|| data->nbr.eight == NULL || data->nbr.nine == NULL)
		return (0);
	return (1);
}

int	ft_load_img(t_data *data)
{
	data->background = fct(data->init, PATH_BACK);
	data->wall = fct(data->init, PATH_WALL);
	data->coll = fct(data->init, PATH_COLL);
	data->exit = fct(data->init, PATH_EXIT);
	data->enemies = fct(data->init, PATH_ENEMIES);
	data->player.img_0 = fct(data->init, "./asset/char/char_0.xpm");
	data->player.img_1 = fct(data->init, "./asset/char/char_1.xpm");
	data->player.img_2 = fct(data->init, "./asset/char/char_2.xpm");
	data->player.img_3 = fct(data->init, "./asset/char/char_3.xpm");
	data->player.img_4 = fct(data->init, "./asset/char/char_4.xpm");
	data->player.img_5 = fct(data->init, "./asset/char/char_5.xpm");
	data->player.img_6 = fct(data->init, "./asset/char/char_6.xpm");
	data->player.img_7 = fct(data->init, "./asset/char/char_7.xpm");
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
