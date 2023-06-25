/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 11:33:18 by loumouli          #+#    #+#             */
/*   Updated: 2022/02/16 14:32:46 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int	ft_basecheck(char *base)
{
	int	i;
	int	j;

	i = 0;
	if (base[0] == 0 || base[1] == 0)
		return (0);
	while (base[i])
	{
		j = 1 + i;
		if (base[i] == '+' || base[i] == '-')
			return (0);
		if (base[i] < 32 || base[i] > 126)
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

int	ft_strlen(char *str)
{
	int	a;

	a = 0;
	while (str[a] != '\0')
	{
		a++;
	}
	return (a);
}

void	ft_putnbr_base(int nbr, char *base)
{
	long	nl;
	int		i;
	int		b[12];

	if (ft_basecheck(base))
	{
		nl = nbr;
		i = 0;
		if (nl < 0)
		{
			nl = nl * -1;
			write(1, "-", 1);
		}
		if (nl == 0)
			write(1, "0", 1);
		while (nl > 0)
		{
			b[i] = nl % ft_strlen(base);
			nl = nl / ft_strlen(base);
			i++;
		}
		while (--i >= 0)
			ft_putchar(base[b[i]]);
	}
}
