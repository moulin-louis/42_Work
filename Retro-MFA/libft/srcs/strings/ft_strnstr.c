/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 16:32:44 by ncoudsi           #+#    #+#             */
/*   Updated: 2021/05/28 04:00:56 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_strings.h"

char	*ft_strnstr(char *haystack, char *needle, size_t len)
{
	size_t	haystack_index;
	size_t	needle_index;

	haystack_index = 0;
	if (needle == NULL || ft_strlen(needle) == 0)
		return (haystack);
	while (haystack[haystack_index] != '\0' && haystack_index < len)
	{
		needle_index = 0;
		while (needle[needle_index] == haystack[haystack_index + needle_index]
			&& haystack_index + needle_index < len)
		{
			if (needle[needle_index + 1] == '\0')
				return (haystack + haystack_index);
			needle_index++;
		}
		haystack_index++;
	}
	return (NULL);
}
