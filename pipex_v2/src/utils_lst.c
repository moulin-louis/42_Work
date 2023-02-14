/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lst_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:07:38 by loumouli          #+#    #+#             */
/*   Updated: 2023/02/14 09:57:47 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_data	*data_lstnew( void )
{
	t_data	*result;

	result = ft_calloc(1, sizeof(t_data));
	if (!result)
		return (NULL);
	result->next = NULL;
	return (result);
}

void	data_lstaddback(t_data **data, t_data *new_tok)
{
	t_data	*temp;

	if (*data == NULL)
	{
		(*data) = new_tok;
		return ;
	}
	temp = *data;
	while (temp->next)
		temp = temp->next;
	new_tok->next = NULL;
	temp->next = new_tok;
}

void	data_tokdel(t_data *tok)
{
	if (tok->cmd_path)
		free(tok->cmd_path);
	if (tok->option)
		clean_array(tok->option);
	if (tok->pipe_fd[0] > 0)
		close(tok->pipe_fd[0]);
	if (tok->pipe_fd[1] > 0)
		close(tok->pipe_fd[1]);
	if (tok->outfile)
		close(tok->outfile);
	free(tok);
}

void	data_lstclear(t_data *data)
{
	t_data	*temp;

	while (data)
	{
		temp = data->next;
		data_tokdel(data);
		data = temp;
	}
}
