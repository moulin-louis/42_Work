/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_comb2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:14:52 by loumouli          #+#    #+#             */
/*   Updated: 2022/02/04 10:56:39 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_print_comb2(void)
{
	int	a;
	int	b;

	a = 0;
	while (a <= 99)
	{
		b = a + 1;
		while (b <= 99)
		{
			ft_putchar('0' + (a / 10));
			ft_putchar('0' + a % 10);
			write(1, " ", 1);
			ft_putchar('0' + (b / 10) % 10);
			ft_putchar('0' + b % 10);
			b++;
			if (a != 98)
			{
				write(1, ", ", 2);
			}	
		}
		a++;
	}
}
