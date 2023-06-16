/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 13:35:50 by loumouli          #+#    #+#             */
/*   Updated: 2022/05/09 17:02:28 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	*libft_ft_memset(void *s, int c, size_t n)
{
	char	*temp;

	temp = s;
	while (n)
	{
		*temp = c;
		temp++;
		n--;
	}
	return (s);
}
