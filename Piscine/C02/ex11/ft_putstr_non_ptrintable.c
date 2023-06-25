/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_non_ptrintable.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:24:09 by loumouli          #+#    #+#             */
/*   Updated: 2022/02/07 18:16:23 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_convtohex(unsigned char c)
{
	ft_putchar("0123456789abcdef"[c / 16]);
	ft_putchar("0123456789abcdef"[c % 16]);
}

void	ft_putstr_non_ptrintable(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] < 32 || str[i] > 126)
		{
			ft_putchar('\\');
			ft_convtohex(str[i]);
		}
		else
			ft_putchar(str[i]);
		i++;
	}
}
