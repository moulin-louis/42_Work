/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:50:26 by loumouli          #+#    #+#             */
/*   Updated: 2022/06/21 16:06:40 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	display_char(t_data *data, int x, int y)
{
	mlx_put_image_to_window(data->init, data->window, data->player.img_0, x, y);
	mlx_put_image_to_window(data->init, data->window, data->player.img_1, x, y);
	mlx_put_image_to_window(data->init, data->window, data->player.img_2, x, y);
	mlx_put_image_to_window(data->init, data->window, data->player.img_3, x, y);
	mlx_put_image_to_window(data->init, data->window, data->player.img_4, x, y);
	mlx_put_image_to_window(data->init, data->window, data->player.img_5, x, y);
	mlx_put_image_to_window(data->init, data->window, data->player.img_6, x, y);
	mlx_put_image_to_window(data->init, data->window, data->player.img_7, x, y);
	mlx_put_image_to_window(data->init, data->window, data->player.img_0, x, y);
	data->pos_x = x;
	data->pos_y = y;
}

void	ft_push_img(t_data *data, int x, int y, int img_type)
{
	if (img_type == '1')
		mlx_put_image_to_window(data->init, data->window, data->wall, x, y);
	else if (img_type == '0')
		mlx_put_image_to_window(data->init, data->window,
			data->background, x, y);
	else if (img_type == 'C')
		mlx_put_image_to_window(data->init, data->window, data->coll, x, y);
	else if (img_type == 'E')
		mlx_put_image_to_window(data->init, data->window, data->exit, x, y);
	else if (img_type == 'P')
		display_char(data, x, y);

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

int	render(t_data *data)
{
	if (data->window != NULL)
		display_char(data, data->pos_x, data->pos_y);
	return (0);
}
