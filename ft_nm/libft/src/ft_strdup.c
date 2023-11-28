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

char	*ft_strdup(const char *s)
{
	size_t len = ft_strlen((char *)s);
	char *result = malloc(len + 1);
	if (!result)
		return (NULL);
	ft_memcpy(result, s, len + 1);
	return (result);
}