/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 15:08:15 by loumouli          #+#    #+#             */
/*   Updated: 2022/07/14 15:05:18 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_check_str(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		i++;
	}
	return (0);
}

int	ft_check_overflow(char *str)
{
	char	*diff;

	diff = ft_itoa(ft_atoi(str));
	if (ft_strncmp(str, diff, ft_strlen(str)) != 0)
		return (free(diff), -1);
	return (free(diff), 1);
}

int	ft_check_double(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = i + 1;
		while (av[j])
		{
			if (ft_strncmp(av[i], av[j], 1000) == 0)
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_check_arg(int ac, char **av)
{
	int	x;

	x = 1;
	if (ac < 2)
		return (-1);
	if (ft_check_double(av) == -1)
		return (-1);
	while (av[x])
	{
		if (ft_check_str(av[x]) == -1)
			return (-1);
		if (ft_check_overflow(av[x]) == -1)
			return (-1);
		x++;
	}
	return (0);
}
