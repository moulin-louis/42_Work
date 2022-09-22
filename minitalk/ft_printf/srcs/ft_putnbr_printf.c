/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_printf.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 13:04:13 by loumouli          #+#    #+#             */
/*   Updated: 2022/05/17 11:12:17 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

static	int	ft_size_nbr(long nbr)
{
	int	result_nbr;

	result_nbr = 0;
	if (nbr == 0)
		return (1);
	while (nbr > 1)
	{
		nbr /= 10;
		result_nbr++;
	}
	if (nbr == 1)
		result_nbr++;
	return (result_nbr);
}

int	ft_putnbr_printf(int nb)
{
	long	lg;
	int		count;

	lg = nb;
	count = 0;
	if (lg < 0)
	{
		lg = lg * -1;
		count += ft_putchar_printf('-');
	}
	count += ft_size_nbr(lg);
	if (lg >= 10)
	{
		ft_putnbr_printf(lg / 10);
		ft_putnbr_printf(lg % 10);
	}
	if ((lg >= 0) && (lg < 10))
		ft_putchar_printf(lg + '0');
	return (count);
}
