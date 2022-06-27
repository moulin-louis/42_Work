/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_score.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:22:16 by loumouli          #+#    #+#             */
/*   Updated: 2022/06/27 12:47:45 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int	fxt(void *init, void *window, void *img, int x, int y)
{
	return (mlx_put_image_to_window(init, window, img, x, y));
}

void	display_nbr(t_data *data, char nbr, int position)
{
	if (nbr == '0')
		fxt(data->init, data->window, data->nbr.zero, position * 18, 0);
	else if (nbr == '1')
		fxt(data->init, data->window, data->nbr.one, position * 18, 0);
	else if (nbr == '2')
		fxt(data->init, data->window, data->nbr.two, position * 18, 0);
	else if (nbr == '3')
		fxt(data->init, data->window, data->nbr.three, position * 18, 0);
	else if (nbr == '4')
		fxt(data->init, data->window, data->nbr.four, position * 18, 0);
	else if (nbr == '5')
		fxt(data->init, data->window, data->nbr.five, position * 18, 0);
	else if (nbr == '6')
		fxt(data->init, data->window, data->nbr.six, position * 18, 0);
	else if (nbr == '7')
		fxt(data->init, data->window, data->nbr.seven, position * 18, 0);
	else if (nbr == '8')
		fxt(data->init, data->window, data->nbr.eight, position * 18, 0);
	else if (nbr == '9')
		fxt(data->init, data->window, data->nbr.nine, position * 18, 0);
}

void	display_score(t_data *data)
{
	char	*nbr;
	int		x;

	nbr = ft_itoa(data->counter);
	x = 0;
	while (nbr[x])
	{
		display_nbr(data, nbr[x], x);
		x++;
	}
	free (nbr);
}
