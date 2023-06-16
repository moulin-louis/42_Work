/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:25:16 by loumouli          #+#    #+#             */
/*   Updated: 2022/05/11 12:09:49 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static	int	ft_count_malloc(char *s, unsigned int start, size_t len)
{
	if (start > len || start > libft_ft_strlen(s))
		return (1);
	if (len > (libft_ft_strlen(s) - start))
		return ((libft_ft_strlen(s) - start) + 1);
	if (len < libft_ft_strlen(s))
		return (len + 1);
	return (0);
}

char	*libft_ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	int		i;
	int		j;
	int		malloc_count;

	malloc_count = ft_count_malloc((char *)s, start, len);
	result = malloc(sizeof(char) * malloc_count);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if ((unsigned int) i >= start && j < (int)len)
		{
			result[j] = s[i];
			j++;
		}
		i++;
	}
	if (j == 0)
		result[0] = '\0';
	else
		result[j] = '\0';
	return (result);
}
