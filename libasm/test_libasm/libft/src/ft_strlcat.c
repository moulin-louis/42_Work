/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 17:45:54 by loumouli          #+#    #+#             */
/*   Updated: 2022/05/09 18:02:37 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

size_t	libft_ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dst[i] && i < size)
		i++;
	if (size == 0 || i >= size)
		return (size + libft_ft_strlen(src));
	j = 0;
	while (src[j] && (i + j < size - 1))
	{
		dst[i + j] = src[j];
		j++;
	}
	dst[i + j] = 0;
	return (i + libft_ft_strlen(src));
}
