/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:48:07 by loumouli          #+#    #+#             */
/*   Updated: 2022/08/29 14:25:11 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/so_long_bonus.h"

void	nullify_nbr_ptr(t_data *data)
{
	data->nbr.zero = NULL;
	data->nbr.one = NULL;
	data->nbr.two = NULL;
	data->nbr.three = NULL;
	data->nbr.four = NULL;
	data->nbr.five = NULL;
	data->nbr.six = NULL;
	data->nbr.seven = NULL;
	data->nbr.eight = NULL;
	data->nbr.nine = NULL;
}

void	nullify_void_ptr(t_data *data)
{
	data->window = NULL;
	data->background = NULL;
	data->wall = NULL;
	data->enemies = NULL;
	data->player.img_0 = NULL;
	data->player.img_1 = NULL;
	data->player.img_2 = NULL;
	data->player.img_3 = NULL;
	data->player.img_4 = NULL;
	data->player.img_5 = NULL;
	data->player.img_6 = NULL;
	data->player.img_7 = NULL;
	data->coll = NULL;
	data->exit = NULL;
	data->counter = 0;
	data->height_windows = 0;
	data->width_windows = 0;
	data->nbr_coll = 0;
	data->pos_x = 0;
	data->pos_y = 0;
	data->ctr_anim = 0;
	nullify_nbr_ptr(data);
}

int	find_nbr_coll(t_data *data)
{
	int	x;
	int	y;
	int	player;

	x = 0;
	player = 0;
	while (data->map[x])
	{
		y = 0;
		while (data->map[x][y])
		{
			if (data->map[x][y] == 'C')
				data->nbr_coll++;
			if (data->map[x][y] == 'P')
				player++;
			y++;
		}
		x++;
	}
	if (player != 1 || data->nbr_coll == 0)
		return (destroy_anything(data), -1);
	return (1);
}

int	check_char_map(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (data->map[x])
	{
		y = 0;
		while (data->map[x][y])
		{
			if (data->map[x][y] != 'P' && data->map[x][y] != '0'
			&& data->map[x][y] != '1' && data->map[x][y] != 'E'
			&& data->map[x][y] != 'C' && data->map[x][y] != 'N')
				return (destroy_anything(data), -1);
			y++;
		}
		x++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		return (ft_printf("Gib the right ammount of arg\n"), 0);
	nullify_void_ptr(&data);
	if (setup_map(&data, av[1]) == -1)
		return (-1);
	if (find_nbr_coll(&data) == -1)
		return (ft_putstr_fd("Error\nProbleme exit/player\n", 1), -4);
	if (check_char_map(&data) == -1)
		return (ft_putstr_fd("Error\nInvalid char\n", 1), 1);
	if (setup_init(&data) == 0)
		return (-3);
	push_map(&data);
	setup_hook(&data);
	mlx_loop(data.init);
	destroy_anything(&data);
	return (0);
}
