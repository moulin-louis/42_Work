/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 11:22:35 by loumouli          #+#    #+#             */
/*   Updated: 2022/05/05 11:50:27 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*libft_ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*result;
	int		i;

	i = 0;
	result = libft_ft_strdup((char *)s);
	if (!f || !s || !result)
		return (NULL);
	while (result[i])
	{
		result[i] = f(i, result[i]);
		i++;
	}
	return (result);
}
