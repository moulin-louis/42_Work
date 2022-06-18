/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 13:49:08 by marnaudy          #+#    #+#             */
/*   Updated: 2022/06/11 14:26:51 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../connect4.h"

int main(int argc, char **argv)
{
	t_game game;

	if (init(&game, argc, argv))
		return (1);
	play_game(&game);
	free(game.board);
}
