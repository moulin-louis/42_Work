/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_move_ai.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 12:32:18 by loumouli          #+#    #+#             */
/*   Updated: 2022/06/12 14:09:08 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../connect4.h"
#include <stdio.h>

int evaluate_position(char *position, int height, int width)
{
	int winner = check_win(position, height, width);
	if (winner == 0)
		return (0);
	int token_count = 0;
	for (int i = 0; i < width; i++)
	{
		int j = height -1;
		while (j >= 0 && position[j * width + i])
			j--;
		token_count += height - 1 - j;
	}
	if (winner == 1)
		return (1000000000 - token_count * 1000);
	return (-1000000000 + token_count * 1000);
}

int	column_order(int i, int width)
{
	if (i % 2)
		return (width / 2 - i / 2 - 1);
	return (width / 2 + i / 2);
}

int	minimax(char *position, int depth, int height, int width,
		int alpha, int beta, int maximizing_player)
{
	if (depth == 0 || game_is_finished(position, height, width))
		return (evaluate_position(position, height, width));
	char *new_board = malloc(width * height * sizeof(char));
	if (!new_board)
	{
		ft_putendl_fd("Malloc error", STDERR_FILENO);
		return (-1);
	}
	ft_memcpy(new_board, position, width * height);
	if (maximizing_player)
	{
		int maxeval = -2000000000;
		for (int i = 0; i < width; i++)
		{
			int x = column_order(i, width);
			if (position[x])
				continue;
			int y = height - 1;
			while (new_board[y * width + x])
				y--;
			new_board[y * width + x] = 1;
			int eval = minimax(new_board, depth - 1, height, width, alpha, beta, 0);
			new_board[y * width + x] = 0;
			if (eval > maxeval)
				maxeval = eval;
			if (eval > alpha)
				alpha = eval;
			if (beta <= alpha)
				break;
		}
		return (free(new_board), maxeval);
	}
	else
	{
		int mineval = 2000000000;
		for (int i = 0; i < width; i++)
		{
			int x = column_order(i, width);
			if (position[x])
				continue;
			int y = height - 1;
			while (new_board[y * width + x])
				y--;
			new_board[y * width + x] = 2;
			int eval = minimax(new_board, depth - 1, height, width, alpha, beta, 1);
			new_board[y * width + x] = 0;
			if (eval < mineval)
				mineval = eval;
			if (eval < beta)
				beta = eval;
			if (beta <= alpha)
				break;
		}
		return (free(new_board), mineval);
	}
}

int depth(int width)
{
	if (width < 10)
		return (8);
	if (width < 16)
		return (6);
	if (width < 20)
		return (5);
	if (width < 30)
		return (4);
	if (width < 70)
		return (3);
	if (width < 150)
		return (2);
	return (1);
}

int	get_move_ai(t_game *game)
{
	char	*new_board;

	new_board = malloc(game->width * game->height * sizeof(char));
	if (!new_board)
	{
		ft_putendl_fd("Malloc error", STDERR_FILENO);
		return (-1);
	}
	ft_memcpy(new_board, game->board, game->width * game->height * sizeof(char));
	int selected_column = 0;
	int	max_eval = -2147483647;
	for (int i = 0; i < game->width; i++)
	{
		int x = column_order(i, game->width);
		if (game->board[x])
			continue;
		int y = game->height - 1;
		while (new_board[y * game->width + x])
			y--;
		new_board[y * game->width + x] = 1;
		int eval = minimax(new_board, depth(game->width), game->height, game->width, -2147483647, 2147483647, 0);
		new_board[y * game->width + x] = 0;
		if (eval > max_eval)
		{
			max_eval = eval;
			selected_column = x;
		}
	}
	free(new_board);
	return (selected_column);
}
