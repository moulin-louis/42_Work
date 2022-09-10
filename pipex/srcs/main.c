/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 14:41:52 by loumouli          #+#    #+#             */
/*   Updated: 2022/09/09 15:48:11 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_exe_cmd(int in, int out, t_data *data, char *cmd)
{
	char	**command;
	char	*cmd_path;
	char	**path;

	path = ft_get_path(data->env);
	if (path == NULL)
		return ;
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
	close(data->io_pipe[0]);
	close(data->io_pipe[1]);
	command = ft_split(cmd, ' ');
	if (command == NULL)
		return ;
	cmd_path = ft_check_access(path, command[0]);
	ft_destroy_dbl_array(path);
	execve(cmd_path, command, data->env);
	ft_destroy_dbl_array(command);
	free(cmd_path);
	free(command);
}

void	ft_waitpid(t_data *data)
{
	int	status;

	waitpid(data->pid1, &status, 0);
	waitpid(data->pid2, &status, 0);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	if (ac != 5)
		return (1);
	if (ft_init_data(&data, av, env) == -1)
		return (-1);
	data.pid1 = fork();
	if (data.pid1 == -1)
		return (-1);
	if (data.pid1 == 0)
		ft_exe_cmd(data.fd_infile, data.io_pipe[1], &data, av[2]);
	data.pid2 = fork();
	if (data.pid2 == -1)
		return (4);
	if (data.pid2 == 0)
	{
		ft_exe_cmd(data.io_pipe[0], data.fd_outfile, &data, av[3]);
	}
	int status;
	waitpid(data.pid1, &status, 0);
	waitpid(data.pid2, &status, 0);
	return (ft_close_stuff(data.fd_infile, data.fd_outfile, data.io_pipe), 0);
}
