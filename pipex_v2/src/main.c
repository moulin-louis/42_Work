/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 12:40:11 by loumouli          #+#    #+#             */
/*   Updated: 2023/02/12 12:40:11 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	dup_in_out(t_data *data, int mode)
{
	if (mode == 1)
	{
		dup2(data->fd_in, STDIN_FILENO);
		dup2(data->pipe_fd[1], STDOUT_FILENO);
		return ;
	}
	dup2(data->pipe_fd[0], STDIN_FILENO);
	dup2(data->fd_out, STDOUT_FILENO);
}

char	*get_path_cmd(t_data *data, char *cmd)
{
	int		x;
	char	*temp;
	char	*temp2;

	x = -1;
	while (data->path[++x])
	{
		temp = ft_strjoin(data->path[x], "/");
		if (temp == NULL)
			perror_n_exit(data, errno);
		temp2 = ft_strjoin(temp, cmd);
		if (temp2 == NULL)
			return (perror("Malloc"), free(temp), NULL);
		if (access(temp2, F_OK | X_OK) == 0)
			return (free(temp), temp2);
		free(temp);
		free(temp2);
	}
	return (NULL);
}

void	ft_exe_without_path(t_data *data, char *input, int mode)
{
	char	**option;

	option = ft_split(input, ' ');
	if (!option)
		perror_n_exit(data, errno);
	if (access(option[0], F_OK | X_OK) == -1)
	{
		clean_array(option);
		perror("acces: ");
		clean_exit(data, 1);
	}
	dup_in_out(data, mode);
	close_all(data);
	execve(option[0], option, data->env);
	perror("execve: ");
	clean_array(option);
	clean_exit(data, 1);
}

void	ft_exe(t_data *data, char *input, int mode)
{
	char	**option;
	char	*path_cmd;

	if (input[0] == '/' || (input[0] == '.' && input[0] == '/'))
		ft_exe_without_path(data, input, mode);
	option = ft_split(input, ' ');
	if (!option)
		perror_n_exit(data, errno);
	path_cmd = get_path_cmd(data, option[0]);
	if (!path_cmd)
	{
		ft_putstr_fd("command not found\n", 2);
		clean_array(option);
		clean_exit(data, 1);
	}
	dup_in_out(data, mode);
	close_all(data);
	execve(path_cmd, option, data->env);
	perror("execve: ");
	free(path_cmd);
	clean_array(option);
	clean_exit(data, 1);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	if (ac != 5)
		return (ft_putstr_fd("Wrong nbr of args\n", 2), 1);
	ft_memset(&data, 0, sizeof(data));
	parse_file_path(&data, av, env);
	data.pid1 = fork();
	if (data.pid1 == 0)
		ft_exe(&data, av[2], 1);
	else
	{
		data.pid2 = fork();
		if (data.pid2 == 0)
			ft_exe(&data, av[3], 2);
		else
		{
			wait_n_close(&data);
			clean_array(data.path);
			exit(0);
		}
	}
}
