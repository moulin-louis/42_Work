/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_and_clean.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 17:38:41 by loumouli          #+#    #+#             */
/*   Updated: 2022/06/27 12:41:30 by loumouli         ###   ########.fr       */
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

void	free_char(t_data *data)
{
	if (data->player.img_0 != NULL)
		mlx_destroy_image(data->init, data->player.img_0);
	if (data->player.img_1 != NULL)
		mlx_destroy_image(data->init, data->player.img_1);
	if (data->player.img_2 != NULL)
		mlx_destroy_image(data->init, data->player.img_2);
	if (data->player.img_3 != NULL)
		mlx_destroy_image(data->init, data->player.img_3);
	if (data->player.img_4 != NULL)
		mlx_destroy_image(data->init, data->player.img_4);
	if (data->player.img_5 != NULL)
		mlx_destroy_image(data->init, data->player.img_5);
	if (data->player.img_6 != NULL)
		mlx_destroy_image(data->init, data->player.img_6);
	if (data->player.img_7 != NULL)
		mlx_destroy_image(data->init, data->player.img_7);
}

void	free_nbr(t_data *data)
{
	if (data->nbr.zero != NULL)
		mlx_destroy_image(data->init, data->nbr.zero);
	if (data->nbr.one != NULL)
		mlx_destroy_image(data->init, data->nbr.one);
	if (data->nbr.two != NULL)
		mlx_destroy_image(data->init, data->nbr.two);
	if (data->nbr.three != NULL)
		mlx_destroy_image(data->init, data->nbr.three);
	if (data->nbr.four != NULL)
		mlx_destroy_image(data->init, data->nbr.four);
	if (data->nbr.five != NULL)
		mlx_destroy_image(data->init, data->nbr.five);
	if (data->nbr.six != NULL)
		mlx_destroy_image(data->init, data->nbr.six);
	if (data->nbr.seven != NULL)
		mlx_destroy_image(data->init, data->nbr.seven);
	if (data->nbr.eight != NULL)
		mlx_destroy_image(data->init, data->nbr.eight);
	if (data->nbr.nine != NULL)
		mlx_destroy_image(data->init, data->nbr.nine);
}

int	destroy_anything(t_data *data)
{
	if (data->background != NULL)
		mlx_destroy_image(data->init, data->background);
	if (data->wall != NULL)
		mlx_destroy_image(data->init, data->wall);
	if (data->coll != NULL)
		mlx_destroy_image(data->init, data->coll);
	if (data->exit != NULL)
		mlx_destroy_image(data->init, data->exit);
	if (data->enemies != NULL)
		mlx_destroy_image(data->init, data->enemies);
	if (data->map != NULL)
		destroy_double_array(data);
	free_char(data);
	free_nbr(data);
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
