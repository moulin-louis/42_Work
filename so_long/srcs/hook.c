/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:52:08 by loumouli          #+#    #+#             */
/*   Updated: 2022/06/14 11:01:59 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	modify_position(t_data *data, int key)
{
	if (key == 'w')
		if (data->character.pos_y - 10 > 0)
		{
			data->character.pos_y -= 10;
			update_frame(data);
			data->counter++;
		}
	if (key == 's')
		if (data->character.pos_y + 10 < (data->background.height_back - data->character.height_char))
		{
			data->character.pos_y += 10;
			update_frame(data);
			data->counter++;
		}
	if (key == 'a')
		if (data->character.pos_x - 10 > 0)
		{
			data->character.pos_x -= 10;
			update_frame(data);
			data->counter++;
		}
	if (key == 'd')
		if (data->character.pos_x + 10 < (data->background.width_back - data->character.width_char))
		{
			data->character.pos_x += 10;
			update_frame(data);
			data->counter++;
		}
}

int	key_event(int key, t_data *data)
{
	if (key == XK_Escape)
		return (close_window(data), 1);
	if (key == 'w' || key == 's' || key == 'a' || key == 'd')
		return (modify_position(data, key), ft_printf(" : %d\n", data->counter), 0);
	return (0);
}

void	setup_hook(t_data *data)
{
	mlx_loop_hook(data->init, &render, data);
	mlx_hook(data->window, KeyPress, KeyPressMask, &key_event, data);
	mlx_hook(data->window, ClientMessage, NoEventMask, &close_window, data);
}
