/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:08:00 by loumouli          #+#    #+#             */
/*   Updated: 2022/05/05 11:31:39 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*libft_ft_strdup(const char *s)
{
	int		len;
	char	*result;
	int		i;

	len = libft_ft_strlen((char *)s);
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (((char *)s)[i])
	{
		result[i] = ((char *)s)[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
