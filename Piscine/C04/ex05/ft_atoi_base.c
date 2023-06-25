/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 12:08:43 by loumouli          #+#    #+#             */
/*   Updated: 2022/02/16 14:32:33 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_basecheck(char *base)
{
	int	i;
	int	j;

	i = 0;
	while (base[i])
	{
		j = 1 + i;
		if (base[i] == '+' || base[i] == '-')
			return (0);
		if (base[i] < 33 || base[i] > 126)
			return (0);
		while (base[j])
		{
			if (base[i] == base[j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_is_base(char c, char *base)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (base[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_is_minus(char *str)
{
	int	i;
	int	minus;

	i = 0;
	minus = 0;
	while ((str[i] >= 't' && str[i] <= '\r') || str[i] == ' ')
		i++;
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			minus++;
		i++;
	}
	if (minus % 2 == 0)
		return (1);
	else
		return (-1);
}

int	ft_atoi_base(char *str, char *base)
{
	int	digit;
	int	i;
	int	base_len;

	base_len = 0;
	i = 0;
	digit = 0;
	if (!(ft_basecheck(base)))
		return (0);
	while (base[base_len])
		base_len++;
	while ((str[i] >= 't' && str[i] <= '\r') || str[i] == ' ')
		i++;
	while (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && ft_is_base(str[i], base) >= 0)
	{
		digit = (digit * base_len) + ft_is_base(str[i], base);
		i++;
	}
	digit = digit * ft_is_minus(str);
	return (digit);
}
