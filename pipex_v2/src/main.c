/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 12:40:11 by loumouli          #+#    #+#             */
/*   Updated: 2023/02/14 10:24:55 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_all(t_data *data)
{
	t_data	*temp;

	temp = data;
	while (temp)
	{
		if (temp->pipe_fd[0] > 0)
			close(temp->pipe_fd[0]);
		if (temp->pipe_fd[1] > 0)
			close(temp->pipe_fd[1]);
		if (temp->outfile > 0)
			close(temp->outfile);
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
	if (!data->cmd_path)
	{
		ft_putstr_fd("command not found : ", 2);
		ft_putstr_fd(data->option[0], 2);
		ft_putstr_fd("\n", 2);
		data_lstclear(first_tok);
		exit(127);
	}
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
	exit (WEXITSTATUS(status));
}

void	print_lst(t_data *data)
{
	int		x;
	t_data	*temp;

	temp = data;
	while (temp)
	{
		printf("cmd_path = %s\n", temp->cmd_path);
		x = -1;
		while (temp->option[++x])
			printf("option[%d] = %s ", x, temp->option[x]);
		printf("\n");
		printf("outfile = %d \n", data->outfile);
		printf("pipe fd[0] = %d \n", temp->pipe_fd[0]);
		printf("pipe fd[1] = %d \n", temp->pipe_fd[1]);
		temp = temp->next;
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;
	t_data	*temp;

	if (ac != 5)
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
