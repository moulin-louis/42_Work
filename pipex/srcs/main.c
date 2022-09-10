/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 14:41:52 by loumouli          #+#    #+#             */
/*   Updated: 2022/09/10 21:20:34 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_exe_cmd(int in, int out, t_data *data, char *cmd);

int	main(int ac, char **av, char **env)
{
	t_data	data;
	int		status;

	if (ac != 5)
		return (ft_printf("wrong nbr of arg\n"), 1);
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
		ft_exe_cmd(data.io_pipe[0], data.fd_outfile, &data, av[3]);
	ft_close_stuff(data.fd_infile, data.fd_infile, data.io_pipe);
	waitpid(data.pid1, &status, 0);
	waitpid(data.pid2, &status, 0);
	return (0);
}

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
	if (cmd_path == NULL)
		return ;
	ft_destroy_dbl_array(path);
	execve(cmd_path, command, data->env);
	ft_destroy_dbl_array(command);
	free(cmd_path);
	free(command);
}

char	**ft_get_path(char **env)
{
	char	**result;
	int		x;
	char	*temp;
	char	*temp2;

	x = 0;
	while (env[x] && !ft_strnstr(env[x], "PATH", 5))
		x++;
	temp = ft_strdup(env[x]);
	if (!temp)
		return (NULL);
	temp2 = ft_strtrim(temp, "PATH=");
	if (!temp2)
		return (free(temp), NULL);
	result = ft_split(temp2, ':');
	if (!result)
		return (free(temp), free(temp2), NULL);
	free(temp);
	free(temp2);
	return (result);
}

char	*ft_check_access(char **path, char *command)
{
	int		x;
	char	*temp;
	char	*temp2;

	x = 0;
	while (path[x])
	{
		temp = ft_strjoin(path[x], "/");
		if (temp == NULL)
			return (NULL);
		temp2 = ft_strjoin(temp, command);
		if (temp2 == NULL)
			return (free(temp), NULL);
		if (access(temp2, F_OK | X_OK) == 0)
			return (free(temp), temp2);
		x++;
		free(temp);
		free(temp2);
	}
	return (NULL);
}