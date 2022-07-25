/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_cpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 14:14:19 by ncoudsi           #+#    #+#             */
/*   Updated: 2021/05/27 17:33:38 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_tabs.h"

void	ft_tab_cpy(void **dst, void **src)
{
	int	index;

	index = 0;
	while (src[index] != NULL)
	{
		dst[index] = src[index];
		index++;
	}
}
