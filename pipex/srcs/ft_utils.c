/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 14:53:49 by loumouli          #+#    #+#             */
/*   Updated: 2022/09/26 17:42:45 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_init_data(int ac, t_data *data, char **av, char **env)
{
	if (ac != 5)
		exit(2);
	data->fd_infile = open(av[1], O_RDONLY);
	if (data->fd_infile <= 0)
		perror("infile");
	data->fd_outfile = open(av[4], O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (data->fd_outfile <= 0)
		perror("outfile");
	data->env = env;
	if (pipe(data->io_pipe) == -1)
		exit(1);
}

void	ft_clean_all(char **path, char **command)
{
	if (command)
		ft_destroy_dbl_array(command);
	if (path)
		ft_destroy_dbl_array(path);
}

int	dup_n_close(t_data *data, int in, int out)
{
	if (dup2(in, STDIN_FILENO) == -1 || dup2(out, STDOUT_FILENO) == -1)
		return (1);
	close(data->io_pipe[0]);
	close(data->io_pipe[1]);
	return (0);
}

void	wait_n_close(t_data *data)
{
	int	status;

	if (data->fd_infile > 0)
		close(data->fd_infile);
	if (data->fd_outfile > 0)
		close(data->fd_outfile);
	close(data->io_pipe[0]);
	close(data->io_pipe[1]);
	waitpid(data->pid1, &status, 0);
	waitpid(data->pid2, &status, 0);
}
