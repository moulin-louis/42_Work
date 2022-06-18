/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 10:48:25 by loumouli          #+#    #+#             */
/*   Updated: 2022/06/12 13:58:59 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../connect4.h"

static void	draw_stones(char c)
{
	if (c == 0)
		ft_putchar_fd(' ', 1);
	if (c == 1)
		ft_putstr_fd("\e[0;33mO\e[0m", 1);
	if (c == 2)
		ft_putstr_fd("\e[0;31mO\e[0m", 1);
}

static void ft_put_colum(t_game *game)
{
	if (game->width / 100)
	{
		for (int x = 1; x <= game->width; x++)
		{
			ft_putchar_fd(' ', 1);
			ft_putchar_fd(x / 100 + '0', 1);
		}
		ft_putchar_fd('\n', 1);
	}
	if (game->width / 10)
	{
		for (int x = 1; x <= game->width; x++)
		{
			ft_putchar_fd(' ', 1);
			ft_putchar_fd(x / 10 % 10 + '0', 1);
		}
		ft_putchar_fd('\n', 1);
	}
	for (int x = 1; x <= game->width; x++)
	{
		ft_putstr_fd(" ", 1);
		ft_putnbr_fd(x % 10, 1);
	}
	ft_putchar_fd('\n', 1);
}

void	display(t_game *game)
{
	int	x;

	x = 0;
	ft_putstr_fd("\033c", 1);
	while (x < (game->height * game->width))
	{
		if (x % game->width == 0 && x != 0)
		{
			ft_putchar_fd('|', 1);
			ft_putchar_fd('\n', 1);
		}
		ft_putchar_fd('|', 1);
		draw_stones(game->board[x]);
		x++;
	}
	ft_putchar_fd('|', 1);
	ft_putchar_fd('\n', 1);
	ft_put_colum(game);
}
