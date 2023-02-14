/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:08:39 by loumouli          #+#    #+#             */
/*   Updated: 2023/02/14 10:39:10 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	**parse_path(t_data *data, char **env)
{
	int		it;
	char	**result;
	char	*temp;
	char	*temp2;

	it = -1;
	while (env[++it] && !ft_strnstr(env[it], "PATH", 5))
		;
	if (env[it] == NULL)
		return (NULL);
	temp = ft_strdup(env[it]);
	if (!temp)
		return (perror("malloc: "), data_lstclear(data), exit(1), NULL);
	temp2 = temp;
	temp = ft_strtrim(temp, "PATH=");
	if (!temp)
		return (perror("malloc: "), data_lstclear(data), exit(1), NULL);
	free(temp2);
	result = ft_split(temp, ':');
	if (!result)
		return (perror("malloc: "), data_lstclear(data), exit(1), NULL);
	free(temp);
	return (result);
}

void	free_2_str(char *str1, char *str2)
{
	free(str1);
	free(str2);
}

char	*dup_cmd(char *cmd, t_data *data)
{
	char	*temp;

	temp = ft_strdup(cmd);
	if (!temp)
		return (perror("malloc: "), data_lstclear(data), exit(1), NULL);
	return (temp);
}

char	*get_path_cmd(t_data *data, char *cmd, char **path)
{
	int		x;
	char	*temp;
	char	*temp2;

	x = -1;
	if (access(cmd, F_OK | X_OK) == 0)
		return (dup_cmd(cmd, data));
	if (!path)
		return (NULL);
	while (path[++x])
	{
		temp = ft_strjoin(path[x], "/");
		if (temp == NULL)
			return (perror("malloc: "), data_lstclear(data), exit(1), NULL);
		temp2 = ft_strjoin(temp, cmd);
		if (temp2 == NULL)
			return (perror("Malloc"), free(temp), exit(1), NULL);
		if (access(temp2, F_OK | X_OK) == 0)
			return (free(temp), temp2);
		free_2_str(temp, temp2);
	}
	return (NULL);
}

void	find_path_cmd(t_data *data)
{
	t_data	*temp;
	char	**path;

	path = parse_path(data, data->env);
	temp = data;
	while (temp)
	{
		temp->cmd_path = get_path_cmd(temp, temp->option[0], path);
		temp = temp->next;
	}
	if (path)
		clean_array(path);
}
