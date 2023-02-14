/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 09:57:45 by loumouli          #+#    #+#             */
/*   Updated: 2023/02/14 10:04:44 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_pipe( t_data *data )
{
	t_data	*temp;

	temp = data;
	while (temp)
	{
		if (pipe(temp->pipe_fd) == -1)
		{
			data_lstclear(data);
			exit(1);
		}
		temp = temp->next;
	}
}

void	parse_command( t_data *data, char **av )
{
	int		x;
	t_data	*temp;

	x = 1;
	temp = data;
	while (av[(++x) + 1])
	{
		temp->option = ft_split(av[x], ' ');
		if (!temp->option)
		{
			perror("malloc: ");
			data_lstclear(temp);
			exit(1);
		}
		temp = temp->next;
	}
}

void	open_file(char **av, t_data *data, int ac)
{
	t_data	*temp;

	if (!data)
		return ;
	close(data->pipe_fd[0]);
	data->pipe_fd[0] = open(av[1], O_RDONLY);
	if (data->pipe_fd[0] == -1)
		perror("infile: ");
	temp = data;
	while (temp->next)
		temp = temp->next;
	temp->outfile = open(av[ac - 1], O_TRUNC | O_CREAT | O_WRONLY, 0000644);
	if (temp->outfile == -1)
	{
		data_lstclear(data);
		perror("outfile: ");
		exit (1);
	}
}

t_data	*parsing( char **av, char **env, int ac)
{
	t_data	*data;
	t_data	*temp;
	int		x;

	data = NULL;
		x = 0;
	while (++x < ac -2)
	{
		temp = data_lstnew();
		if (!temp)
			return (data_lstclear(data), NULL);
		temp->env = env;
		data_lstaddback(&data, temp);
	}
	init_pipe(data);
	parse_command(data, av);
	find_path_cmd(data);
	open_file(av, data, ac);
	return (data);
}
