/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 14:41:52 by loumouli          #+#    #+#             */
/*   Updated: 2022/09/16 17:03:40 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	t_data	data;

	if (ac != 5)
		return (ft_printf("wrong nbr of arg\n"), 1);
	if (ft_init_data(&data, av, env) == -1)
		return (-1);
	data.pid1 = fork();
	if (data.pid1 == -1)
		return (perror("Fork"), -1);
	if (data.pid1 == 0)
	{
		if (ft_exe_cmd(data.fd_infile, data.io_pipe[1], &data, av[2]) == 5)
			ft_printf("command not found : %s\n", av[2]);
	}
	else if (data.pid1 > 0)
	{
		data.pid2 = fork();
		if (data.pid2 == -1)
			return (perror("Fork"), 4);
		if (data.pid2 == 0)
			{
				if (ft_exe_cmd(data.io_pipe[0], data.fd_outfile, &data, av[3]) == 5)
				ft_printf("command not found : %s\n", av[3]);
			}
		else if (data.pid2 > 0)
			wait_n_close(&data);
	}
	return (0);
}

int	ft_exe_cmd(int in, int out, t_data *data, char *cmd)
{
	char	**command;
	char	*cmd_path;
	char	**path;

	if (ft_strchr(cmd, '/'))
		return (ft_exe_without_path(in, out, data, cmd));
	path = ft_get_path(data->env);
	if (path == NULL && ft_strchr(cmd, '/') == 0)
		return (5);
	if (dup2(in, STDIN_FILENO) == -1 || dup2(out, STDOUT_FILENO) == -1)
		return (perror("Dup"), 1);
	close(data->io_pipe[0]);
	close(data->io_pipe[1]);
	command = ft_split(cmd, ' ');
	if (command == NULL)
		return (perror("Malloc"), ft_clean_all(path, command), 1);
	cmd_path = ft_check_access(path, command[0]);
	if (cmd_path == NULL)
		return (perror("Malloc"), ft_clean_all(path, command), 1);
	execve(cmd_path, command, NULL);
	ft_clean_all(path, command);
	free(cmd_path);
	return (perror("Execve"),1);
}

int	ft_exe_without_path(int in, int out, t_data *data, char *cmd)
{
	char	**command;

	if (dup2(in, STDIN_FILENO) == -1 || dup2(out, STDOUT_FILENO) == -1)
		return (perror("Dup"), 1);
	close(data->io_pipe[0]);
	close(data->io_pipe[1]);
	if (access(cmd, F_OK | X_OK) != 0)
		return (perror("Acces"), 1);
	command = ft_split(cmd, ' ');
	if (command == NULL)
		return (perror("Malloc"), 1);
	execve(command[0], command, NULL);
	ft_destroy_dbl_array(command);
	return (perror("Execve"), 1);
}

char	**ft_get_path(char **env)
{
	char	**result;
	int		x;
	char	*temp;
	char	*temp2;

	x = 0;
	if (env[0] == NULL)
		return (NULL);
	while (env[x] && !ft_strnstr(env[x], "PATH", 5))
		x++;
	if (env[x] == NULL)
		return (NULL);
	temp = ft_strdup(env[x]);
	if (!temp)
		return (perror("Malloc"), NULL);
	temp2 = temp;
	temp = ft_strtrim(temp, "PATH=");
	if (!temp)
		return (perror("Malloc"), free(temp2), NULL);
	free(temp2);
	result = ft_split(temp, ':');
	if (!result)
		return (perror("Malloc"), free(temp), NULL);
	free(temp);
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
			return (perror("Malloc"), NULL);
		temp2 = ft_strjoin(temp, command);
		if (temp2 == NULL)
			return (perror("Malloc"), free(temp), NULL);
		if (access(temp2, F_OK | X_OK) == 0)
			return (free(temp), temp2);
		x++;
		free(temp);
		free(temp2);
	}
	return (NULL);
}