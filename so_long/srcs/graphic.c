/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:50:26 by loumouli          #+#    #+#             */
/*   Updated: 2022/06/26 14:39:28 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	animate_player(t_data *data)
{
	static int	x;

	if (x == 0)
		mlx_put_image_to_window(data->init, data->window, data->player.img_0,
			data->pos_x, data->pos_y);
	else if (x == 1)
		mlx_put_image_to_window(data->init, data->window, data->player.img_1,
			data->pos_x, data->pos_y);
	else if (x == 2)
		mlx_put_image_to_window(data->init, data->window, data->player.img_2,
			data->pos_x, data->pos_y);
	else if (x == 3)
		mlx_put_image_to_window(data->init, data->window, data->player.img_3,
			data->pos_x, data->pos_y);
	else if (x == 4)
		mlx_put_image_to_window(data->init, data->window, data->player.img_4,
			data->pos_x, data->pos_y);
	else if (x == 5)
	{
		mlx_put_image_to_window(data->init, data->window, data->player.img_5,
			data->pos_x, data->pos_y);
		x = 0;
	}
	if (x != 5)
		x++;
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
	else if (img_type == 'N')
		mlx_put_image_to_window(data->init, data->window, data->enemies, x, y);
	else if (img_type == 'P')
	{
		data->pos_x = x;
		data->pos_y = y;
		animate_player(data);
	}
}

void	push_map(t_data *data)
{
	int	x;
	int	y;
	int	i;
	int	j;

	x = 0;
	y = 32;
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

int	close_window(t_data *data, int win)
{
	if (win == 1)
		ft_printf("You win !\n");
	else if (win == 0)
		ft_printf("You loose !\n");
	mlx_destroy_window(data->init, data->window);
	data->window = NULL;
	return (1);
}

int	render(t_data *data)
{
	data->ctr_anim++;
	if (data->window != NULL)
	{
		//display_score(data);
		if (data->ctr_anim % 1500 == 0)
			animate_player(data);
	}
	return (0);
}
