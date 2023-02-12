/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 12:35:59 by loumouli          #+#    #+#             */
/*   Updated: 2023/02/12 12:35:59 by loumouli         ###   ########.fr       */
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
	int		pipe_fd[2];
	int		fd_in;
	int		fd_out;
	long	pid1;
	long	pid2;
	char	**env;
	char	**path;
}	t_data;

int		ft_strcmp(char *s1, char *s2);
void	open_file(t_data *data, char **av);
void	parse_path(t_data *data, char **env);
void	wait_n_close(t_data *data);
void	close_all(t_data *data);
void	clean_exit(t_data *data, int err);
void	perror_n_exit(t_data *data, int err);
void	parse_file_path(t_data *data, char **av, char **env);

#endif
