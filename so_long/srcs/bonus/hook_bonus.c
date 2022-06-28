/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:52:08 by loumouli          #+#    #+#             */
/*   Updated: 2022/06/28 10:50:57 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/so_long_bonus.h"

int	find_player(t_data *data, int *i, int *j)
{
	*i = 0;
	while (data->map[*i])
	{
		*j = 0;
		while (data->map[*i][*j])
		{
			if (data->map[*i][*j] == 'P')
				return (1);
			(*j)++;
		}
		(*j) = 0;
		(*i)++;
	}
	(void)*j;
	(void)*i;
	return (0);
}

void	modify_pos(t_data *data, int key)
{
	int	j;
	int	i;
	int	temp;

	j = 0;
	i = 0;
	temp = data->counter;
	find_player(data, &i, &j);
	if (key == 'w')
		move_up(data, i, j);
	else if (key == 's')
		move_down(data, i, j);
	else if (key == 'a')
		move_left(data, i, j);
	else if (key == 'd')
		move_right(data, i, j);
	if (temp != data->counter && data->window != NULL)
		ft_printf("SCORE : %d\n", data->counter);
}

int	key_event(int key, t_data *data)
{
	if (key == XK_Escape)
		return (close_window(data, -1), 1);
	if (key == 'w' || key == 's' || key == 'a' || key == 'd')
		return (modify_pos(data, key), 0);
	return (0);
}

void	setup_hook(t_data *data)
{
	mlx_loop_hook(data->init, &render, data);
	mlx_hook(data->window, KeyPress, KeyPressMask, &key_event, data);
	mlx_hook(data->window, ClientMessage, NoEventMask, &close_window, data);
}
