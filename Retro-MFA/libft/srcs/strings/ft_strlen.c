/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 14:01:19 by ncoudsi           #+#    #+#             */
/*   Updated: 2021/05/28 04:01:28 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_strings.h"

size_t	ft_strlen(char *src)
{
	size_t	result;

	result = 0;
	if (src == NULL)
		return (0);
	while (src[result] != '\0')
		result++;
	return (result);
}
