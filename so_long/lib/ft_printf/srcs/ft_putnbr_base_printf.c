/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_printf.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 12:28:35 by loumouli          #+#    #+#             */
/*   Updated: 2022/05/17 11:08:08 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

static	int	ft_nbr_equal_zero(void)
{
	ft_putchar_printf('0');
	return (1);
}

int	ft_putnbr_base_printf(int nbr, char *base)
{
	long	nl;
	int		i;
	int		b[12];
	int		count;
	int		size_len;

	nl = nbr;
	i = 0;
	count = 0;
	size_len = ft_strlen(base);
	if (nl < 0)
		nl = (unsigned int)nl;
	if (nl == 0)
		return (ft_nbr_equal_zero());
	while (nl > 0)
	{
		b[i++] = nl % size_len;
		nl = nl / size_len;
	}
	while (--i >= 0)
		count += ft_putchar_printf(base[b[i]]);
	return (count);
}
