/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 12:53:46 by ldutriez          #+#    #+#             */
/*   Updated: 2022/05/26 15:04:49 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_strings.h"

void	ft_bzero(void *addr, size_t n)
{
	size_t	i;
	char	*tmp;

	i = 0;
	tmp = addr;
	while (i < n)
	{
		tmp[i] = 0;
		++i;
	}
}
