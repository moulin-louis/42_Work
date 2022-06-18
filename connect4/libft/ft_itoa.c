/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 17:17:46 by marnaudy          #+#    #+#             */
/*   Updated: 2021/11/24 13:09:13 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static unsigned int	ft_nb_size(int n)
{
	unsigned int	size;
	unsigned int	pos_nb;

	size = 1;
	pos_nb = n;
	if (n < 0)
	{
		size++;
		pos_nb = -1 * n;
	}
	while (pos_nb / 10)
	{
		size++;
		pos_nb /= 10;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char			*new;
	unsigned int	i;
	unsigned int	size;
	unsigned int	pos_nb;

	size = ft_nb_size(n);
	new = malloc(sizeof(char) * (size + 1));
	if (!new)
		return (NULL);
	pos_nb = n;
	if (n < 0)
	{
		pos_nb = -1 * n;
		new[0] = '-';
	}
	new[size] = 0;
	i = size - 1;
	new[i] = pos_nb % 10 + '0';
	while (pos_nb / 10)
	{
		i--;
		pos_nb /= 10;
		new[i] = pos_nb % 10 + '0';
	}
	return (new);
}
