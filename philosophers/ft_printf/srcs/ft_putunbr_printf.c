/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr_printf.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 15:20:31 by loumouli          #+#    #+#             */
/*   Updated: 2022/05/16 15:43:51 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

static	int	ft_size_unbr(unsigned long nbr)
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

int	ft_putunbr_printf(unsigned int nb)
{
	int		count;
	long	lg;

	lg = nb;
	count = ft_size_unbr(lg);
	if (lg >= 10)
	{
		ft_putunbr_printf(lg / 10);
		ft_putunbr_printf(lg % 10);
	}
	else if (lg < 10)
		ft_putchar_printf(lg + '0');
	return (count);
}
