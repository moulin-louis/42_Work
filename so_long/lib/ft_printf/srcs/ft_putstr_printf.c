/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_printf.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 15:46:43 by loumouli          #+#    #+#             */
/*   Updated: 2022/06/21 12:26:42 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

int	ft_putstr_printf(char *s)
{
	int	x;

	x = 0;
	if (!s)
		return (ft_putstr_printf("(null)"));
	while (s[x])
		x += ft_putchar_printf(s[x]);
	return (x);
}
