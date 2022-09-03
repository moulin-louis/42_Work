/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 15:08:15 by loumouli          #+#    #+#             */
/*   Updated: 2022/09/03 18:51:44 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

int	ft_check_arg(int ac, char ***av)
{
	int	x;

	x = 1;
	if (ac < 2)
		return (ft_putstr_fd("Wrong nbr of arg", 1), -1);
	else if (ac == 2)
		*av = ft_split_custom((*av)[1], ' ');
	while ((*av)[x])
	{
		if (ft_check_str((*av)[x]) == -1)
			return (ft_putstr_fd("Unwanted chr", 1), ft_destroy_split(*av), -1);
		x++;
	}
	return (0);
}
