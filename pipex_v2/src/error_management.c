/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:55:48 by loumouli          #+#    #+#             */
/*   Updated: 2023/02/12 15:28:05 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_all(t_data *data)
{
	close(data->fd_in);
	close(data->fd_out);
	close(data->pipe_fd[0]);
	close(data->pipe_fd[1]);
}

void	clean_exit(t_data *data, int err)
{
	if (data->path)
		clean_array(data->path);
	close_all(data);
	exit(err);
}

void	perror_n_exit(t_data *data, int err)
{
	perror("malloc: ");
	clean_exit(data, err);
}
