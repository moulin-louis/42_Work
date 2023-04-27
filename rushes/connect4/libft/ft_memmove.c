/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 21:14:31 by marnaudy          #+#    #+#             */
/*   Updated: 2021/11/24 11:32:50 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned int	i;
	int				start;
	int				inc;

	if (!src && !dest)
		return (dest);
	i = 0;
	start = 0;
	inc = 1;
	if (dest > src)
	{
		start = n - 1;
		inc = -1;
	}
	while (i < n)
	{
		((char *) dest)[start + i * inc] = ((char *) src)[start + i * inc];
		i++;
	}
	return (dest);
}
