/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 14:58:48 by loumouli          #+#    #+#             */
/*   Updated: 2022/09/09 15:02:38 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_get_path(char **env)
{
	char	**result;
	int		x;
	char	*temp;
	char	*temp2;

	x = 0;
	while (env[x] && !ft_strnstr(env[x], "PATH", 5))
		x++;
	temp = ft_strdup(env[x]);
	if (!temp)
		return (NULL);
	temp2 = ft_strtrim(temp, "PATH=");
	if (!temp2)
		return (free(temp), NULL);
	result = ft_split(temp2, ':');
	if (!result)
		return (free(temp), free(temp2), NULL);
	free(temp);
	free(temp2);
	return (result);
}

char	*ft_check_access(char **path, char *command)
{
	int		x;
	char	*temp;
	char	*temp2;

	x = 0;
	while (path[x])
	{
		temp = ft_strjoin(path[x], "/");
		temp2 = ft_strjoin(temp, command);
		if (access(temp2, F_OK | X_OK) == 0)
			return (free(temp), temp2);
		x++;
		free(temp);
		free(temp2);
	}
	return (NULL);
}
