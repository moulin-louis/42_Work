/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_position.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 08:55:50 by loumouli          #+#    #+#             */
/*   Updated: 2022/06/26 14:37:52 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	move_up(t_data *data, int i, int j)
{
	if (data->map[i - 1][j] == 'C')
	{
		data->nbr_coll--;
		data->counter++;
		data->map[i - 1][j] = 'P';
		data->map[i][j] = '0';
	}
	else if (data->map[i - 1][j] == '0')
	{
		data->counter++;
		data->map[i - 1][j] = 'P';
		data->map[i][j] = '0';
	}
	else if (data->map[i - 1][j] == 'E' && data->nbr_coll == 0)
	{
		data->counter++;
		close_window(data, 1);
	}
	else if (data->map[i - 1][j] == 'N')
		close_window(data, 0);
	if (data->window != NULL && data->map[i - 1][j] != '1')
		push_map(data);
}

void	move_down(t_data *data, int i, int j)
{
	if (data->map[i + 1][j] == 'C')
	{
		data->nbr_coll--;
		data->counter++;
		data->map[i + 1][j] = 'P';
		data->map[i][j] = '0';
	}
	else if (data->map[i + 1][j] == '0')
	{
		data->counter++;
		data->map[i + 1][j] = 'P';
		data->map[i][j] = '0';
	}
	else if (data->map[i + 1][j] == 'E' && data->nbr_coll == 0)
	{
		data->counter++;
		close_window(data, 1);
	}
	else if (data->map[i + 1][j] == 'N')
		close_window(data, 0);
	if (data->window != NULL && data->map[i + 1][j] != '1')
		push_map(data);
}

void	move_left(t_data *data, int i, int j)
{
	if (data->map[i][j -1] == 'C')
	{
		data->nbr_coll--;
		data->counter++;
		data->map[i][j - 1] = 'P';
		data->map[i][j] = '0';
	}
	else if (data->map[i][j - 1] == '0')
	{
		data->counter++;
		data->map[i][j - 1] = 'P';
		data->map[i][j] = '0';
	}
	else if (data->map[i][j - 1] == 'E' && data->nbr_coll == 0)
	{
		data->counter++;
		close_window(data, 1);
	}
	else if (data->map[i][j - 1] == 'N')
		close_window(data, 0);
	if (data->window != NULL && data->map[i][j - 1] != '1')
		push_map(data);
}

void	move_right(t_data *data, int i, int j)
{
	if (data->map[i][j + 1] == 'C')
	{
		data->nbr_coll--;
		data->counter++;
		data->map[i][j + 1] = 'P';
		data->map[i][j] = '0';
	}
	else if (data->map[i][j + 1] == '0')
	{
		data->counter++;
		data->map[i][j + 1] = 'P';
		data->map[i][j] = '0';
	}
	else if (data->map[i][j + 1] == 'E' && data->nbr_coll == 0)
	{
		data->counter++;
		close_window(data, 1);
	}
	else if (data->map[i][j + 1] == 'N')
		close_window(data, 0);
	if (data->window != NULL && data->map[i][j + 1] != '1')
		push_map(data);
}
