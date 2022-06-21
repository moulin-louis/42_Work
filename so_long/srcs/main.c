/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:48:07 by loumouli          #+#    #+#             */
/*   Updated: 2022/06/21 12:30:44 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	find_nbr_coll(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	while (data->map[x])
	{
		y = 0;
		while (data->map[x][y])
		{
			if (data->map[x][y] == 'C')
				data->nbr_coll++;
			y++;
		}
		x++;
	}
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		return (ft_printf("Gib the right ammount of arg\n"), 0);
	nullify_void_ptr(&data);
	if (setup_map(&data, av[1]) == -1)
		return (-1);
	if (setup_init(&data) == 0)
		return (-3);
	find_nbr_coll(&data);
	push_map(&data);
	setup_hook(&data);
	mlx_loop(data.init);
	destroy_anything(&data);
	return (0);
}
