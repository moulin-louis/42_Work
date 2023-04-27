/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect4.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 09:53:29 by marnaudy          #+#    #+#             */
/*   Updated: 2022/06/11 17:06:32 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONNECT4_H
# define CONNECT4_H

# include "libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <time.h>

typedef struct s_game
{
	int		width;
	int		height;
	char	*board;
}	t_game;

int		ft_atoi_no_overflow(char *s);
int		init(t_game *game, int argc, char **argv);
void	display(t_game *game);
int		get_move_player(t_game *game);
int		get_move_ai(t_game *game);
int		check_win(char *board, int height, int width);
int		check_input(t_game *game);
void	play_game(t_game *game);
int 	game_is_finished(char *board, int height, int width);

#endif
