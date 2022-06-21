/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 17:24:56 by loumouli          #+#    #+#             */
/*   Updated: 2022/06/21 12:36:06 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	nullify_void_ptr(t_data *data)
{
	data->window = NULL;
	data->background = NULL;
	data->wall = NULL;
	data->player = NULL;
	data->coll = NULL;
	data->exit = NULL;
	data->counter = 0;
	data->pos_x = 0;
	data->pos_y = 0;
	data->height = 0;
	data->width = 0;
	data->nbr_coll = 0;
}

int	ft_load_img(t_data *data)
{
	int	n;

	data->background = mlx_xpm_file_to_image(data->init, PATH_BACK, &n, &n);
	data->wall = mlx_xpm_file_to_image(data->init, PATH_WALL, &n, &n);
	data->player = mlx_xpm_file_to_image(data->init, PATH_PLAYER, &n, &n);
	data->coll = mlx_xpm_file_to_image(data->init, PATH_COLL, &n, &n);
	data->exit = mlx_xpm_file_to_image(data->init, PATH_EXIT, &n, &n);
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
		return (destroy_anything(data), 0);
	data->window = mlx_new_window(data->init, data->width, data->height,
			"so_long");
	if (data->window == NULL)
		return (ft_printf("Error\nError mlx_new_windows\n"), 0);
	return (1);
}
