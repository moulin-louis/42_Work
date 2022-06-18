/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_win.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 11:18:56 by marnaudy          #+#    #+#             */
/*   Updated: 2022/06/11 17:07:25 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../connect4.h"

int check_win_pos(char *board, int height, int width, int line, int col)
{
	int player = board[line * width + col];

	if (col < width - 3)
	{
		if (line < height - 3)
		{
			//Check diagonal going down and to the right
			for (int i = 1; i < 4; i++)
			{
				if (board[(line + i) * width + col + i] != player)
					break;
				if (i == 3)
					return (player);
			}
		}
		if (line >= 3)
		{
			//Check diagonal going up and to the right
			for (int i = 1; i < 4; i++)
			{
				if (board[(line - i) * width + col + i] != player)
					break;
				if (i == 3)
					return (player);
			}
		}
		//Check horizontal
		for (int i = 1; i < 4; i++)
		{
			if (board[line * width + col + i] != player)
				break;
			if (i == 3)
				return (player);
		}
	}
	if (line < height - 3)
	{
		//Check vertical
		for (int i = 1; i < 4; i++)
		{
			if (board[(line + i) * width + col] != player)
				break;
			if (i == 3)
				return (player);
		}
	}
	return (0);
}

int	check_win(char *board, int height, int width)
{
	int	winning_player;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (board[i * width + j])
			{
				winning_player = check_win_pos(board, height, width, i, j);
				if (winning_player)
					return (winning_player);
			}
		}
	}
	return (0);
}
