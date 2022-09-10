/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 14:41:52 by loumouli          #+#    #+#             */
/*   Updated: 2022/09/10 20:19:49 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_close(int in, t_data *data)
{
	if (in == data->io_pipe[0])
	{
		ft_putstr_fd("je suis dans enfant 2", STDOUT_FILENO);	
		close(data->io_pipe[1]);
	}
	else
	{
		ft_putstr_fd("je suis dans enfant 1", STDOUT_FILENO);
		close(data->io_pipe[0]);
	}
}

void	ft_exe_cmd(int in, int out, t_data *data, char *cmd)
{
	char	**command;
	char	*cmd_path;
	char	**path;

	path = ft_get_path(data->env);
	if (path == NULL)
		return ;
	if (out == data->io_pipe[1])
		ft_printf("je suis dans enfant 1\n");
	else
		ft_printf("Je suis dans enfant 2\n");
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
	ft_close(in, data);
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
	{
		ft_exe_cmd(data.fd_infile, data.io_pipe[1], &data, av[2]);
	}
	data.pid2 = fork();
	ft_printf("pid2 = %d\n", data.pid2);
	if (data.pid2 == -1)
		return (4);
	if (data.pid2 == 0)
	{
		ft_exe_cmd(data.io_pipe[0], data.fd_outfile, &data, av[3]);
	}
	ft_printf("je suis dans parent\n");
	int status;
	waitpid(data.pid1, &status, 0);
	ft_printf("je suis dans parent encore une fois\n");
	waitpid(data.pid2, &status, 0);
	return (ft_close_stuff(data.fd_infile, data.fd_outfile, data.io_pipe), 0);
}
