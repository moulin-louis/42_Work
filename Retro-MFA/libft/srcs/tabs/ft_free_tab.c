/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 14:13:46 by ncoudsi           #+#    #+#             */
/*   Updated: 2021/05/27 17:46:51 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_tabs.h"

void	ft_free_tab(void **tab)
{
	int	index;

	index = 0;
	while (tab[index] != NULL)
	{
		free(tab[index]);
		tab[index] = NULL;
		index++;
	}
	free(tab);
}
