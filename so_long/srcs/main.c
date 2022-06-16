/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:48:07 by loumouli          #+#    #+#             */
/*   Updated: 2022/06/15 14:13:50 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	setup_init(t_data *data)
{
	data->init = mlx_init();
	if (data->init)
	{
		data->background.back_ptr = mlx_xpm_file_to_image(data->init, PATH_BACK,
				&data->background.width_back, &data->background.height_back);
		data->character.char_ptr = mlx_xpm_file_to_image(data->init, PATH_CHAR,
				&data->character.width_char, &data->character.height_char);
		data->window = mlx_new_window(data->init, data->background.width_back,
				data->background.height_back, "so_long");
		if (!data->window)
			free(data->init);
	}
	mlx_put_image_to_window(data->init, data->window,
		data->background.back_ptr, 0, 0);
	mlx_put_image_to_window(data->init, data->window, data->character.char_ptr,
		data->character.pos_x, data->character.pos_y);
}

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

void	destroy_anything(t_data *data)
{
	if (data->background.back_ptr)
		mlx_destroy_image(data->init, data->background.back_ptr);
	if (data->character.char_ptr)
		mlx_destroy_image(data->init, data->character.char_ptr);
	if (data->init)
	{
		mlx_destroy_display(data->init);
		free(data->init);
	}
	if (data->map)
		destroy_double_array(data);
}

int	main(void)
{
	t_data	data;

	data.counter = 0;
	data.character.pos_x = 300;
	data.character.pos_y = 300;
	if (setup_map(&data) == -1)
		return (ft_putstr_fd("Error\n", 1), 1);
	setup_init(&data);
	if (data.window == NULL || !data.init)
		return (1);
	setup_hook(&data);
	mlx_loop(data.init);
	destroy_anything(&data);
}
