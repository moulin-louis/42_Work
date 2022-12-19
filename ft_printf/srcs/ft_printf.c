/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 18:18:30 by loumouli          #+#    #+#             */
/*   Updated: 2022/12/19 16:01:26 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

int	ft_write_arg(int i, va_list ap, int count, char *str)
{
	count = 0;
	if (str[i] == 'c')
		count = ft_putchar_printf((char)va_arg(ap, int));
	else if (str[i] == 'l' && str[i + 1] == 'd')
		count = ft_putnbr_long_printf(va_arg(ap, unsigned long));
	else if (str[i] == 's')
		count = ft_putstr_printf(va_arg(ap, char *));
	else if (str[i] == 'i' || str[i] == 'd')
		count = ft_putnbr_printf(va_arg(ap, int));
	else if (str[i] == '%')
		count += ft_putchar_printf('%');
	else if (str[i] == 'x')
		count = ft_putnbr_base_printf(va_arg(ap, int), "0123456789abcdef");
	else if (str[i] == 'X')
		count = ft_putnbr_base_printf(va_arg(ap, int), "0123456789ABCDEF");
	else if (str[i] == 'u')
		count = ft_putunbr_printf(va_arg(ap, int));
	else if (str[i] == 'p')
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
			count += ft_write_arg(i + 1, ap, count, (char *)str);
			if (str[i + 1] == 'l' && str[i + 2] == 'd')
				i++;
			i += 2;
		}
		else if (str[i])
			count += ft_putchar_printf(str[i++]);
	}
	return (count);
}
