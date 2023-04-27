/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 13:50:27 by marnaudy          #+#    #+#             */
/*   Updated: 2022/06/12 11:48:26 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../connect4.h"

int	play_first()
{
	srand(time(NULL));
	return (rand() % 2);
}

int play_round_human(t_game *game)
{
	int	n = get_move_player(game);
	if (n < 0)
		return (-1);
	int	i = game->height - 1;
	while (game->board[i * game->width + n] && i)
		i--;
	game->board[i * game->width + n] = 2;
	return (0);
}

int play_round_ai(t_game *game)
{
	int	n = get_move_ai(game);
	if (n < 0)
		return (-1);
	int	i = game->height - 1;
	while (game->board[i * game->width + n] && i)
		i--;
	game->board[i * game->width + n] = 1;
	ft_putendl_fd("AI has played", STDOUT_FILENO);
	return (0);
}

int board_is_full(char *board, int width)
{
	for (int i = 0; i < width; i++)
	{
		if (!board[i])
			return (0);
	}
	return (1);
}

int game_is_finished(char *board, int height, int width)
{
	return (board_is_full(board, width) || check_win(board, height, width));
}

void	display_end_message(t_game *game)
{
	int winning_player;

	winning_player = check_win(game->board, game->height, game->width);
	if (winning_player == 1)
		ft_putendl_fd("You lost :(", STDOUT_FILENO);
	else if (winning_player == 2)
		ft_putendl_fd("You won :)", STDOUT_FILENO);
	else
		ft_putendl_fd("It's a tie", STDOUT_FILENO);
}

void	play_game(t_game *game)
{
	int	player = play_first() + 1;
	while (!game_is_finished(game->board, game->height, game->width))
	{
		display(game);
		if (player == 2)
		{
			if (play_round_human(game))
				return;
			player = 1;
		}
		else
		{
			if (play_round_ai(game))
				return;
			player = 2;
		}
	}
	display(game);
	display_end_message(game);
}
