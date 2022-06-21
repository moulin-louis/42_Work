/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_and_clean.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 17:38:41 by loumouli          #+#    #+#             */
/*   Updated: 2022/06/21 12:33:25 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	destroy_double_array(t_data *data)
{
	int	x;

	x = 0;
	while (data->map[x])
	{
		free(data->map[x]);
		x++;
	}
	if (!data->map[x])
		free (data->map[x]);
	free (data->map);
}

int	destroy_anything(t_data *data)
{
	if (data->background != NULL)
		mlx_destroy_image(data->init, data->background);
	if (data->wall != NULL)
		mlx_destroy_image(data->init, data->wall);
	if (data->coll != NULL)
		mlx_destroy_image(data->init, data->coll);
	if (data->player != NULL)
		mlx_destroy_image(data->init, data->player);
	if (data->exit != NULL)
		mlx_destroy_image(data->init, data->exit);
	if (data->map != NULL)
		destroy_double_array(data);
	if (data->window != NULL)
	{
		mlx_destroy_window(data->init, data->window);
		data->window = NULL;
	}
	if (data->init != NULL)
	{
		mlx_destroy_display(data->init);
		free(data->init);
	}
	return (1);
}
