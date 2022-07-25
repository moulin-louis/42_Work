/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str_tab.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 21:11:20 by ldutriez          #+#    #+#             */
/*   Updated: 2021/05/27 17:30:09 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_io.h"

void	ft_print_str_tab(char *name, char **tab)
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
	while (tab && tab[index])
	{
		ft_putnbr(index);
		ft_putstr("--->[");
		ft_putstr(tab[index]);
		ft_putstr("]\n");
		index++;
	}
	ft_putstr("-----===-----\n");
}
