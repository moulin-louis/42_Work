/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 12:29:15 by ldutriez          #+#    #+#             */
/*   Updated: 2021/05/28 04:01:19 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_strings.h"

char	*ft_strstr(char *haystack, char *needle)
{
	int	haystack_index;
	int	needle_index;

	haystack_index = 0;
	if (!*needle)
		return (haystack);
	while (haystack[haystack_index] != '\0')
	{
		needle_index = 0;
		if (needle[needle_index] == haystack[haystack_index])
		{
			while (needle[needle_index] != '\0'
				&& haystack[haystack_index + needle_index]
				== needle[needle_index])
				needle_index++;
			if (needle[needle_index] == '\0')
				return (haystack + haystack_index);
		}
		haystack_index++;
	}
	return (NULL);
}
