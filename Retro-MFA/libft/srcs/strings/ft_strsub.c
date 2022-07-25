/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 15:55:01 by ncoudsi           #+#    #+#             */
/*   Updated: 2021/05/28 04:01:46 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_strings.h"

char	*ft_strsub(char *src, size_t start, size_t len)
{
	size_t	index;
	char	*result;

	index = 0;
	result = NULL;
	if (src == NULL || len == 0 || start + len > ft_strlen(src))
		return (NULL);
	result = ft_strnew(len);
	if (result == NULL)
		return (NULL);
	while (index < len)
	{
		result[index] = src[start + index];
		index++;
	}
	result[index] = '\0';
	return (result);
}
