/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_long.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 16:01:43 by loumouli          #+#    #+#             */
/*   Updated: 2022/12/19 16:01:51 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

int	size_long_nbr(long nbr)
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

int	ft_putnbr_long_printf(long nb)
{
	int		count;

	count = size_long_nbr(nb);
	if (nb >= 10)
	{
		ft_putnbr_long_printf(nb / 10);
		ft_putnbr_long_printf(nb % 10);
	}
	if ((nb >= 0) && (nb < 10))
		ft_putchar_printf(nb + '0');
	return (count);
}
