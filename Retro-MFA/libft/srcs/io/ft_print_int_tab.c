/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int_tab.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 21:00:33 by ldutriez          #+#    #+#             */
/*   Updated: 2021/05/27 17:29:47 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_io.h"

void	ft_print_int_tab(char *name, int *tab, size_t len)
{
	size_t		index;

	index = 0;
	if (name != NULL)
	{
		ft_putchar('{');
		ft_putstr(name);
		ft_putstr("}\n");
	}
	ft_putstr("-----===-----\n");
	while (tab && index < len)
	{
		ft_putnbr(index);
		ft_putstr("--->[");
		ft_putnbr(tab[index]);
		ft_putstr("]\n");
		index++;
	}
	ft_putstr("-----===-----\n");
}
