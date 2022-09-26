/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli < loumouli@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 14:41:52 by loumouli          #+#    #+#             */
/*   Updated: 2022/09/26 13:10:41 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	t_data	data;

	ft_init_data(ac, &data, av, env);
	data.pid1 = fork();
	if (data.pid1 == -1)
		return (perror("Fork"), 2);
	if (data.pid1 == 0)
	{
		if (data.fd_infile > 0)
			ft_exe_cmd(data.fd_infile, data.io_pipe[1], &data, av[2]);
	}
	else if (data.pid1 > 0)
	{
		data.pid2 = fork();
		if (data.pid2 == -1)
			return (perror("Fork"), 3);
		if (data.pid2 == 0)
		{
			if (data.fd_outfile > 0)
				ft_exe_cmd(data.io_pipe[0], data.fd_outfile, &data, av[3]);
		}
		else if (data.pid2 > 0)
			wait_n_close(&data);
	}
}

int	ft_exe_cmd(int in, int out, t_data *data, char *cmd)
{
	char	**command;
	char	*cmd_path;
	char	**path;

	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
		return (ft_exe_without_path(in, out, data, cmd));
	path = ft_get_path(data->env);
	if (path == NULL)
		return (ft_printf("command not found : %s\n", cmd), 1);
	command = ft_split(cmd, ' ');
	if (command == NULL)
		return (perror("Malloc"), ft_clean_all(path, command), 1);
	cmd_path = ft_check_access(path, command[0]);
	if (cmd_path == NULL)
		return (ft_printf("command not found : %s\n", cmd),
			ft_clean_all(path, command), 5);
	if (dup_n_close(data, in, out) == 1)
		return (1);
	execve(cmd_path, command, data->env);
	return (perror("execve"), ft_clean_all(path, command), free(cmd_path), 1);
}

int	ft_exe_without_path(int in, int out, t_data *data, char *cmd)
{
	char	**command;

	if (dup_n_close(data, in, out) == 1)
		return (1);
	if (access(cmd, F_OK | X_OK) != 0)
		return (perror("Acces"), 1);
	command = ft_split(cmd, ' ');
	if (command == NULL)
		return (perror("Malloc"), 1);
	execve(command[0], command, NULL);
	return (ft_destroy_dbl_array(command), perror("Execve"), 1);
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
