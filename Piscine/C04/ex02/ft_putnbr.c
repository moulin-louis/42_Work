/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 11:31:35 by loumouli          #+#    #+#             */
/*   Updated: 2022/02/09 11:32:24 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int nb)
{
	long	lg;

	lg = nb;
	if (lg < 0)
	{
		lg = lg * -1;
		ft_putchar('-');
	}
	if (lg >= 10)
	{
		ft_putnbr(lg / 10);
		ft_putnbr(lg % 10);
	}
	if ((lg >= 0) && (lg < 10))
	{
		ft_putchar(lg + '0');
	}
}
