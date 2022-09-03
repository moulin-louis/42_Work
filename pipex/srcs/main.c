/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 14:41:52 by loumouli          #+#    #+#             */
/*   Updated: 2022/09/03 16:29:05 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_get_path(char **env)
{
	char	**result;
	int		x;

	x = 32;
	while (env[x] && !ft_strnstr(env[x], "PATH", 5))
		x++;
	env[x] = ft_strtrim(env[x], "PATH=");
	if (!env[x])
		return (NULL);
	result = ft_split(env[x], ':');
	if (!result)
		return (NULL);
	return result ;
}

int	main(int ac, char **av, char **env)
{
	char	**path;
	(void)ac;
	(void)av;
	path = ft_get_path(env);
	if (path == NULL)
		return (ft_printf("cand find path sry looser\n"), -1);
	int x = 0;
	while (path[x])
	{
		ft_printf("[%s]\n", path[x]);
		x++;
	}
	(void)path;
	return 0;
}
