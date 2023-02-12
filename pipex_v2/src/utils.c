/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 13:24:57 by loumouli          #+#    #+#             */
/*   Updated: 2023/02/12 15:28:19 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_file(t_data *data, char **av)
{
	data->fd_in = open(av[1], O_RDONLY);
	if (data->fd_in < 0)
		perror("infile: ");
	data->fd_out = open(av[4], O_TRUNC | O_CREAT | O_WRONLY, 0000644);
	if (data->fd_out < 0)
	{
		perror("outfile: ");
		return ;
	}
	if (data->fd_in < 0)
		exit (1);
	if (pipe(data->pipe_fd) == -1)
	{
		perror("pipe init: ");
		exit (1);
	}
}

void	parse_path(t_data *data, char **env)
{
	int		it;
	char	*temp;
	char	*temp2;

	it = -1;
	while (env[++it] && !ft_strnstr(env[it], "PATH", 5))
		;
	if (env[it] == NULL)
		return ;
	temp = ft_strdup(env[it]);
	if (!temp)
		perror_n_exit(data, errno);
	temp2 = temp;
	temp = ft_strtrim(temp, "PATH=");
	if (!temp)
		perror_n_exit(data, errno);
	free(temp2);
	data->path = ft_split(temp, ':');
	if (!data->path)
	{
		free(temp);
		perror_n_exit(data, errno);
	}
	free(temp);
}

void	wait_n_close(t_data *data)
{
	int	status;

	close_all(data);
	waitpid(data->pid1, &status, 0);
	waitpid(data->pid2, &status, 0);
}

void	parse_file_path(t_data *data, char **av, char **env)
{
	open_file(data, av);
	data->env = env;
	parse_path(data, env);
}
