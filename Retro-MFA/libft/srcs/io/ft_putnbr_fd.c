/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 15:00:18 by ncoudsi           #+#    #+#             */
/*   Updated: 2021/05/27 17:30:23 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_io.h"

void	ft_putnbr_fd(int fd, int nbr)
{
	if (nbr < 0)
	{
		ft_putchar_fd(fd, '-');
		nbr = nbr * -1;
	}
	if (nbr >= 10)
		ft_putnbr_fd(fd, nbr / 10);
	ft_putchar_fd(fd, (nbr % 10) + '0');
}
