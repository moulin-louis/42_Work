/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:48:07 by loumouli          #+#    #+#             */
/*   Updated: 2022/06/04 16:39:59 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/so_long.h"

int	encode_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	render(t_data *data)
{
	//int trgb = encode_trgb(1, 255, 0, 0);
	if (data->window != NULL)
		mlx_pixel_put(data->init, data->window, 5, 5, 0x00ff0000);
	return (0);
}

int	close_window(t_data *data)
{
	mlx_destroy_window(data->init, data->window);
	return (1);
}

int	key_event(int key, t_data *data)
{
	data->counter++;
	ft_putnbr_fd(data->counter, 1);
	ft_putchar_fd('\n', 1);
	if (key == XK_Escape)
		close_window(data);
	return (0);
}

int	main(void)
{
	t_data	data;

	data.counter = 0;
	data.init = mlx_init();
	if (!data.init)
		return (3);

	data.window = mlx_new_window(data.init, WINDOW_WIDTH, WINDOW_HEIGHT, "so_long");
	if (!data.window)
		return (free(data.init), 3);

	mlx_hook(data.window, KeyPress, KeyPressMask, &key_event, &data);
	mlx_hook(data.window, ClientMessage, NoEventMask, &close_window, &data);
	mlx_loop_hook(data.init, &render, &data);


	mlx_loop(data.init);

	mlx_destroy_display(data.init);
}
