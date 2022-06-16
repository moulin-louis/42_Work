/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:50:26 by loumouli          #+#    #+#             */
/*   Updated: 2022/06/08 14:57:03 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int	render(t_data *data)
{
	(void)data;
	return (0);
}

int	update_frame(t_data *data)
{
	if (data->window == NULL)
		return (1);
	ft_printf("TWO IMAGE PUSH");
	mlx_put_image_to_window(data->init, data->window, data->background.back_ptr,
		0, 0);
	mlx_put_image_to_window(data->init, data->window, data->character.char_ptr,
		data->character.pos_x, data->character.pos_y);
	return (0);
}

int	close_window(t_data *data)
{
	mlx_destroy_window(data->init, data->window);
	data->window = NULL;
	return (1);
}
