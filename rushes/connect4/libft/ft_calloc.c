/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 17:07:24 by marnaudy          #+#    #+#             */
/*   Updated: 2021/11/24 11:32:11 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*new;
	size_t	i;

	new = malloc(nmemb * size);
	if (!new)
		return (NULL);
	i = 0;
	while (i < nmemb * size)
	{
		((char *)new)[i] = 0;
		i++;
	}
	return (new);
}
