/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 10:03:14 by loumouli          #+#    #+#             */
/*   Updated: 2022/02/21 14:46:43 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	*ft_range(int min, int max)
{
	int	diff;
	int	*dest;
	int	i;

	if (min >= max)
		return (0);
	diff = max - min;
	dest = malloc(diff * sizeof(int));
	if (!dest)
		return (NULL);
	i = 0;
	while (min < max)
	{
		dest[i] = min;
		min++;
		i++;
	}
	return (dest);
}
