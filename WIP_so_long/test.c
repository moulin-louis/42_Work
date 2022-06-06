/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:48:07 by loumouli          #+#    #+#             */
/*   Updated: 2022/06/06 18:48:31 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/so_long.h"
#include <unistd.h>
#include <time.h>
#include <stdio.h>


int	render(t_data *data)
{
	(void)data;
	return (0);
}

int	update_frame(t_data *data, int key)
{
	ft_putstr_fd("NOUVELLE FRAME PUSH", 1);
	if (data->window == NULL)
		return (1);
	mlx_put_image_to_window(data->init, data->window, data->background, 0, 0);
	mlx_put_image_to_window(data->init, data->window, data->character, data->position_char_x, data->position_char_y);
	return (0);
}

int	close_window(t_data *data)
{
	mlx_destroy_window(data->init, data->window);
	data->window = NULL;
	return (1);
}

int	key_event(int key, t_data *data)
{
	if (key == XK_Escape)
		close_window(data);
	data->counter++;
	if (key == 'w')
		if (data->position_char_y - 10 > 0)
			data->position_char_y -= 10;
	if (key == 's')
		if (data->position_char_y + 10 < (WINDOW_HEIGHT - data->height_img_1))
			data->position_char_y += 10;
	if (key == 'a')
		if (data->position_char_x - 10 > 0)
			data->position_char_x -= 10;
	if (key == 'd')
		if (data->position_char_x + 10 < (WINDOW_WIDTH - data->width_img_1))
			data->position_char_x += 10;
	if (key == 'w' || key == 's' || key == 'a' || key == 'd')
		update_frame(data, key);
	ft_putnbr_fd(data->counter, 1);
	ft_putchar_fd('\n', 1);
	return (0);
}

int	main(void)
{
	t_data	data;

	data.counter = 0;
	data.position_char_x = 300;
	data.position_char_y = 300;

	data.init = mlx_init();
	if (!data.init)
		return (3);

	data.window = mlx_new_window(data.init, WINDOW_WIDTH, WINDOW_HEIGHT, "so_long");
	if (!data.window)
		return (free(data.init), 3);

	data.background = mlx_xpm_file_to_image(data.init, "./cool_asset/test/background.xpm", &data.width_img_1, &data.height_img_1);
	data.character = mlx_xpm_file_to_image(data.init, "./cool_asset/test/character.xpm", &data.width_img_1, &data.height_img_1);

	if (data.window == NULL)
		return (1);
	mlx_put_image_to_window(data.init, data.window, data.background, 0, 0);
	mlx_put_image_to_window(data.init, data.window, data.character, data.position_char_x, data.position_char_y);

	mlx_loop_hook(data.init, &render, &data);
	mlx_hook(data.window, KeyPress, KeyPressMask, &key_event, &data);
	mlx_hook(data.window, ClientMessage, NoEventMask, &close_window, &data);

	mlx_loop(data.init);

	mlx_destroy_image(data.init, data.background);
	mlx_destroy_image(data.init, data.character);
	mlx_destroy_display(data.init);
	free(data.init);
}
