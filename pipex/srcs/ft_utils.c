/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 14:53:49 by loumouli          #+#    #+#             */
/*   Updated: 2022/09/17 18:18:35 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_init_data(t_data *data, char **av, char **env)
{
	data->fd_infile = open(av[1], O_RDONLY);
	if (data->fd_infile <= 0)
		perror("infile");
	data->fd_outfile = open(av[4], O_WRONLY | O_CREAT, 0644);
	if (data->fd_outfile <= 0)
		return (close(data->fd_infile), perror("outfile"), -1);
	if (data->fd_infile <= 0)
		return (close(data->fd_outfile), -1);
	if (pipe(data->io_pipe) == -1)
		return (-1);
	data->env = env;
	data->status_child[0] = 0;
	data->status_child[1] = 0;
	return (0);
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
	int	exit_code_1;
	int	exit_code_2;

	close(data->fd_infile);
	close(data->fd_outfile);
	close(data->io_pipe[0]);
	close(data->io_pipe[1]);
	waitpid(data->pid1, &status, 0);
	exit_code_1 = WEXITSTATUS(status);
	waitpid(data->pid2, &status, 0);
	exit_code_2 = WEXITSTATUS(status);
	ft_printf("exit code child 1 = %d\n", exit_code_1);
	ft_printf("exit code child 2 = %d\n", exit_code_2);
}
