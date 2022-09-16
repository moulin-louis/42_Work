/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 14:53:49 by loumouli          #+#    #+#             */
/*   Updated: 2022/09/16 17:13:20 by loumouli         ###   ########.fr       */
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
		return (perror("outfile"), close(data->fd_infile), -1);
	if (pipe(data->io_pipe) == -1)
		return (-1);
	data->env = env;
	return (0);
}

void	ft_clean_all(char **path, char **command)
{
	if (command)
		ft_destroy_dbl_array(command);
	if (path)
		ft_destroy_dbl_array(path);
}

void	wait_n_close(t_data *data)
{
	int	status;
	
	close(data->fd_infile);
	close(data->fd_outfile);
	close(data->io_pipe[0]);
	close(data->io_pipe[1]);
	waitpid(data->pid1, &status, 0);
	waitpid(data->pid2, &status, 0);
}
