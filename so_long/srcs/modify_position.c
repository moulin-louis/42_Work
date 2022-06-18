/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_position.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 08:55:50 by loumouli          #+#    #+#             */
/*   Updated: 2022/06/18 13:34:49 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	move_up(t_data *data, int i, int j)
{
	if (data->map[i - 1][j] == 'C')
	{
		data->nbr_coll--;
		data->counter++;
		ft_printf("%d\n", data->counter);
		data->map[i - 1][j] = 'P';
		data->map[i][j] = '0';
	}
	else if (data->map[i - 1][j] == '0')
	{
		data->counter++;
		ft_printf("%d\n", data->counter);
		data->map[i - 1][j] = 'P';
		data->map[i][j] = '0';
	}
	else if (data->map[i - 1][j] == 'E' && data->nbr_coll == 0)
	{
		data->counter++;
		ft_printf("%d\n", data->counter);
		close_window(data);
	}
	if (data->window != NULL && data->map[i - 1][j] != '1')
		push_map(data);
}

void	move_down(t_data *data, int i, int j)
{
	if (data->map[i + 1][j] == 'C')
	{
		data->nbr_coll--;
		data->counter++;
		ft_printf("%d\n", data->counter);
		data->map[i + 1][j] = 'P';
		data->map[i][j] = '0';
	}
	else if (data->map[i + 1][j] == '0')
	{
		data->counter++;
		ft_printf("%d\n", data->counter);
		data->map[i + 1][j] = 'P';
		data->map[i][j] = '0';
	}
	else if (data->map[i + 1][j] == 'E' && data->nbr_coll == 0)
	{
		data->counter++;
		ft_printf("%d\n", data->counter);
		close_window(data);
	}
	if (data->window != NULL && data->map[i + 1][j] != '1')
		push_map(data);
}

void	move_left(t_data *data, int i, int j)
{
	if (data->map[i][j -1] == 'C')
	{
		data->nbr_coll--;
		data->counter++;
		ft_printf("%d\n", data->counter);
		data->map[i][j - 1] = 'P';
		data->map[i][j] = '0';
	}
	else if (data->map[i][j - 1] == '0')
	{
		data->counter++;
		ft_printf("%d\n", data->counter);
		data->map[i][j - 1] = 'P';
		data->map[i][j] = '0';
	}
	else if (data->map[i][j - 1] == 'E' && data->nbr_coll == 0)
	{
		data->counter++;
		ft_printf("%d\n", data->counter);
		close_window(data);
	}
	if (data->window != NULL && data->map[i][j - 1] != '1')
		push_map(data);
}

void	move_right(t_data *data, int i, int j)
{
	if (data->map[i][j + 1] == 'C')
	{
		data->nbr_coll--;
		data->counter++;
		ft_printf("%d\n", data->counter);
		data->map[i][j + 1] = 'P';
		data->map[i][j] = '0';
	}
	else if (data->map[i][j + 1] == '0')
	{
		data->counter++;
		ft_printf("%d\n", data->counter);
		data->map[i][j + 1] = 'P';
		data->map[i][j] = '0';
	}
	else if (data->map[i][j + 1] == 'E' && data->nbr_coll == 0)
	{
		data->counter++;
		ft_printf("%d\n", data->counter);
		close_window(data);
	}
	if (data->window != NULL && data->map[i][j + 1] != '1')
		push_map(data);
}
