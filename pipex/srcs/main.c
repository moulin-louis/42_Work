/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 14:41:52 by loumouli          #+#    #+#             */
/*   Updated: 2022/09/04 21:38:24 by loumouli         ###   ########.fr       */
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
		if (access(temp2, F_OK) == 0 && access(temp2, X_OK) == 0)
			return (free(temp), temp2);
		x++;
		free(temp);
		free(temp2);
	}
	return (NULL);
}

void	ft_destroy_split(char **av)
{
	int	x;

	x = -1;
	while (av[++x])
		free(av[x]);
	free(av);
}

int	main(int ac, char **av, char **env)
{
	char	**path;
	char	*cmdpath;

	if (ac == 1)
		return (0);
	path = ft_get_path(env);
	if (path == NULL)
		return (ft_printf("cand find path\n"), -1);
	cmdpath = ft_check_access(path, av[1]);
	if (cmdpath == NULL)
		return (ft_printf("Cant access command"), ft_destroy_split(path), -2);
	execve(cmdpath, options, env);
	free(cmdpath);
	ft_destroy_split(path);
	return (0);
}
