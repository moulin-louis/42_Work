/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 12:40:11 by loumouli          #+#    #+#             */
/*   Updated: 2023/02/13 13:33:00 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	close_all(t_data *data)
{
	t_data	*temp;

	temp = data;
	while (temp)
	{
		close(temp->pipe_fd[0]);
		close(temp->pipe_fd[1]);
		temp = temp->next;
	}
}

void	ft_execute(t_data *data, t_data *first_tok)
{
	dup2(data->pipe_fd[0], STDIN_FILENO);
	if (data->next)
		dup2(data->next->pipe_fd[1], STDOUT_FILENO);
	else if (!data->outfile)
		dup2(data->pipe_fd[1], STDOUT_FILENO);
	else
		dup2(data->outfile, STDOUT_FILENO);
	close_all(first_tok);
	execve(data->cmd_path, data->option, data->env);
	perror("execve: ");
	data_lstclear(first_tok);
	exit(1);
}

void	wait_n_clear(t_data *data)
{
	t_data	*temp;
	int		status;

	while (data)
	{
		temp = data->next;
		waitpid(data->pid, &status, 0);
		data_tokdel(data);
		data = temp;
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;
	t_data	*temp;

	if (ac < 5)
		return (ft_putstr_fd("Wrong nbr of args\n", 2), 1);
	data = parsing(av, env, ac);
	temp = data;
	while (data)
	{
		if (data->pipe_fd[0] < 0)
		{
			data = data->next;
			continue ;
		}
		data->pid = fork();
		if (data->pid == 0)
			ft_execute(data, temp);
		else
			data = data->next;
	}
	data = temp;
	close_all(data);
	wait_n_clear(data);
}
