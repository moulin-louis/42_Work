/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 12:35:59 by loumouli          #+#    #+#             */
/*   Updated: 2023/02/14 09:56:59 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <errno.h>

typedef struct s_data
{
	int				pipe_fd[2];
	int				outfile;
	long			pid;
	char			**option;
	char			*cmd_path;
	char			**env;
	struct s_data	*next;
}	t_data;

void	close_all(t_data *data);
t_data	*parsing(char **av, char **env, int ac);
t_data	*data_lstnew( void );
void	data_lstaddback(t_data **data, t_data *new_tok);
void	data_tokdel(t_data *tok);
void	data_lstclear(t_data *data);
void	find_path_cmd(t_data *data);

#endif