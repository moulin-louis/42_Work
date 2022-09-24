/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli < loumouli@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 15:59:06 by loumouli          #+#    #+#             */
/*   Updated: 2022/09/24 22:47:15 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/server.h"

char	*ft_realloc_str(char *src, int len)
{
	int			i;
	char		*result;

	i = 0;
	if (!src)
	{
		result = malloc(2);
		if (!result)
			return (NULL);
		result[0] = '\0';
		return (result);
	}
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	while (src[i])
	{
		result[i] = src[i];
		i++;
	}
	result[i] = '\0';
	free(src);
	return (result);
}