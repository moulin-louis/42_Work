/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 18:18:30 by loumouli          #+#    #+#             */
/*   Updated: 2022/09/03 14:32:32 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

int	ft_putchar_printf(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr_printf(char *s)
{
	int	x;

	x = 0;
	if (s == NULL)
		return (ft_putstr_printf("(null)"));
	while (s[x])
		x += ft_putchar_printf(s[x]);
	return (x);
}

int	ft_write_arg(char c, va_list ap, int count)
{
	count = 0;
	if (c == 'c')
		count = ft_putchar_printf((char)va_arg(ap, int));
	else if (c == 's')
		count = ft_putstr_printf(va_arg(ap, char *));
	else if (c == 'i' || c == 'd')
		count = ft_putnbr_printf(va_arg(ap, int));
	else if (c == '%')
		count += ft_putchar_printf('%');
	else if (c == 'x')
		count = ft_putnbr_base_printf(va_arg(ap, int), "0123456789abcdef");
	else if (c == 'X')
		count = ft_putnbr_base_printf(va_arg(ap, int), "0123456789ABCDEF");
	else if (c == 'u')
		count = ft_putunbr_printf(va_arg(ap, int));
	else if (c == 'p')
		count = ft_print_adress_printf(va_arg(ap, unsigned long),
				"0123456789abcdef");
	return (count);
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		i;
	int		count;

	i = 0;
	count = 0;
	va_start(ap, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			count += ft_write_arg(str[i + 1], ap, count);
			i += 2;
		}
		else if (str[i])
			count += ft_putchar_printf(str[i++]);
	}
	return (count);
}
