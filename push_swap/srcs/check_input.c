/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 15:08:15 by loumouli          #+#    #+#             */
/*   Updated: 2022/08/25 17:05:50 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

int	ft_check_str(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] == '\0')
		return (-1);
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

int	ft_check_arg(int ac, char ***av)
{
	int	x;

	x = 1;
	if (ac < 2)
		return (ft_putstr_fd("Wrong nbr of arg", 1), -1);
	else if (ac == 2)
		*av = ft_split_custom((*av)[1], ' ');
	if (ft_check_double(*av) == -1)
			return (ft_destroy_split(*av),ft_putstr_fd("same nbr 2 time", 1), -1);
	while ((*av)[x])
	{
		if (ft_check_str((*av)[x]) == -1)
			return (ft_putstr_fd("Unwanted char in args",1), ft_destroy_split(*av), -1);
		x++;
	}
	return (0);
}
