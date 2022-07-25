/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 13:46:00 by ncoudsi           #+#    #+#             */
/*   Updated: 2021/05/27 17:33:15 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_strings.h"

char	*ft_strdup(char *src)
{
	int		index;
	int		len;
	char	*result;

	if (src == NULL)
		return (NULL);
	len = ft_strlen(src);
	result = ft_strnew(len);
	if (result == NULL)
		return (NULL);
	index = 0;
	while (index < len)
	{
		result[index] = src[index];
		index++;
	}
	return (result);
}
