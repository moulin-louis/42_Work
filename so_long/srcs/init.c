/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 17:24:56 by loumouli          #+#    #+#             */
/*   Updated: 2022/07/25 15:37:25 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	*fct(void *init, char *path)
{
	int	n;

	return (mlx_xpm_file_to_image(init, path, &n, &n));
}

int	ft_load_img(t_data *data)
{
	data->background = fct(data->init, PATH_BACK);
	data->wall = fct(data->init, PATH_WALL);
	data->coll = fct(data->init, PATH_COLL);
	data->exit = fct(data->init, PATH_EXIT);
	data->player = fct(data->init, "./asset/char/char_0.xpm");
	if (data->background == NULL || data->wall == NULL || data->player == NULL)
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
		return (ft_printf("Error Fail load image\n"), destroy_anything(data), 0);
	data->window = mlx_new_window(data->init, data->width_windows,
			data->height_windows,
			"so_long");
	if (data->window == NULL)
		return (ft_printf("Error\nError mlx_new_windows\n"), 0);
	return (1);
}
