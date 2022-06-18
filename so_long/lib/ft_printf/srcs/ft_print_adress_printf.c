/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_adress_printf.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 15:41:46 by loumouli          #+#    #+#             */
/*   Updated: 2022/05/17 11:04:40 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

int	ft_nbr_equal_zero(void)
{
	ft_putstr_printf("(nil)");
	return (5);
}

int	ft_print_adress_printf(unsigned long nbr, char *base)
{
	int		i;
	long	b[25];
	int		count;
	int		size_len;

	i = 0;
	count = 0;
	size_len = ft_strlen(base);
	if (nbr == 0)
		return (ft_nbr_equal_zero());
	count += ft_putstr_printf("0x");
	while (nbr > 0)
	{
		b[i++] = nbr % size_len;
		nbr = nbr / size_len;
	}
	while (--i >= 0)
		count += ft_putchar_printf(base[b[i]]);
	return (count);
}
