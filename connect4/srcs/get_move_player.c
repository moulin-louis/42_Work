/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_move_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 10:57:44 by marnaudy          #+#    #+#             */
/*   Updated: 2022/06/11 14:19:52 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../connect4.h"

int	get_move_player(t_game *game)
{
	char	*input;
	int		nb_input;

	do
	{
		ft_putstr_fd("Choose input column : ", 1);
		input = get_next_line(STDIN_FILENO);
		if (!input)
			return (-1);
		nb_input = ft_atoi_no_overflow(input);
		free(input);
		if (nb_input < 1 || nb_input > game->width)
			ft_putendl_fd("You need to enter a valid column number", STDOUT_FILENO);
		else if (game->board[nb_input - 1])
			ft_putendl_fd("That column is full", STDOUT_FILENO);
	} while (nb_input < 1 || nb_input > game->width
		|| game->board[nb_input - 1]);
	return (nb_input - 1);
}
