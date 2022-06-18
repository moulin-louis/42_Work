/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:50:26 by loumouli          #+#    #+#             */
/*   Updated: 2022/06/18 13:33:13 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int	render(t_data *data)
{
	(void)data;
	return (0);
}

void	ft_push_img(t_data *data, int x, int y, int img_type)
{
	if (img_type == '1')
		mlx_put_image_to_window(data->init, data->window, data->wall, x, y);
	if (img_type == 'C')
		mlx_put_image_to_window(data->init, data->window, data->coll, x, y);
	if (img_type == 'E')
		mlx_put_image_to_window(data->init, data->window, data->exit, x, y);
	if (img_type == 'P')
		mlx_put_image_to_window(data->init, data->window, data->player, x, y);
	if (img_type == '0')
		mlx_put_image_to_window(data->init, data->window,
			data->background, x, y);
}

void	push_map(t_data *data)
{
	int	x;
	int	y;
	int	i;
	int	j;

	x = 0;
	y = 0;
	i = 0;
	j = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			ft_push_img(data, x, y, data->map[i][j]);
			x += 32;
			j++;
		}
		y += 32;
		x = 0;
		i++;
	}
}

int	close_window(t_data *data)
{
	mlx_destroy_window(data->init, data->window);
	data->window = NULL;
	return (1);
}
