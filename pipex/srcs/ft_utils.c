/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 14:53:49 by loumouli          #+#    #+#             */
/*   Updated: 2022/09/10 20:28:22 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_close_stuff(int fd_in, int fd_out, int io_pipe[2])
{
	close(fd_in);
	close(fd_out);
	close(io_pipe[0]);
	close(io_pipe[1]);
}

int	ft_open(t_data *data, char **av)
{
	data->fd_infile = open(av[1], O_RDONLY);
	if (data->fd_infile <= 0)
		return (-1);
	data->fd_outfile = open(av[4], O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (data->fd_outfile <= 0)
		return (close(data->fd_infile), -1);
	return (0);
}

int	ft_init_data(t_data *data, char **av, char **env)
{
	if (ft_open(data, av) == -1)
		return (-1);
	if (pipe(data->io_pipe) == -1)
		return (-1);
	data->env = env;
	return (0);
}
