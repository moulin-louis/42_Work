/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:50:33 by loumouli          #+#    #+#             */
/*   Updated: 2022/05/11 12:09:08 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	*libft_ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	x;
	char	*result;
	char	*temp_src;

	x = 0;
	if (!dest && !src)
		return (NULL);
	result = (char *)dest;
	temp_src = (char *)src;
	while (x < n)
	{
		*result = *temp_src;
		result++;
		temp_src++;
		x++;
	}
	return ((void *)result - x);
}
