/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 12:14:38 by loumouli          #+#    #+#             */
/*   Updated: 2022/06/12 13:54:29 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../connect4.h"

int		check_input(t_game *game)
{
	if (game->width < 7 || game->height < 6)
		return (0);
	if ((game->width * game->height) / game->width != game->height)
		return (0);
	return (1);
}

int	init(t_game *game, int argc, char **argv)
{
	if (argc != 3)
	{
		if (argc > 3)
			ft_putendl_fd("Too many arguments", STDERR_FILENO);
		if (argc < 3)
			ft_putendl_fd("Too few arguments", STDERR_FILENO);
		return (-1);
	}
	game->height = ft_atoi_no_overflow(argv[1]);
	game->width = ft_atoi_no_overflow(argv[2]);
	if (game->height < 0 || game->width < 0)
	{
		ft_putendl_fd("Invalid size", STDERR_FILENO);
		return (-1);
	}
	if (game->height > 200 || game->width > 200)
	{
		ft_putendl_fd("Game is too big", STDERR_FILENO);
		return (-1);
	}
	if (check_input(game) == 0)
	{
		ft_putendl_fd("Invalid size", STDERR_FILENO);
		return (-2);
	}
	game->board = ft_calloc(sizeof(char), (game->height * game->width + 1));
	if (!game->board)
	{
		ft_putendl_fd("Malloc error", STDERR_FILENO);
		return (-3);
	}
	return (0);
}
