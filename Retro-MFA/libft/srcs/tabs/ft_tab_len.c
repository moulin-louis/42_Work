/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_len.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 14:13:14 by ncoudsi           #+#    #+#             */
/*   Updated: 2021/05/27 17:33:38 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_tabs.h"

int	ft_tab_len(void **tab)
{
	int	index;

	index = 0;
	if (tab == NULL)
	{
		return (index);
	}
	while (tab[index] != NULL)
		index++;
	return (index);
}
