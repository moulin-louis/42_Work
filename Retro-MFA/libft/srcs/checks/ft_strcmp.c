/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 14:55:32 by ncoudsi           #+#    #+#             */
/*   Updated: 2021/05/27 17:35:44 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_checks.h"

t_bool	ft_strcmp(char *src, char *target)
{
	size_t	index;

	index = 0;
	if (src == NULL || target == NULL)
		return (0);
	while (src[index] != '\0' || target[index] != '\0')
	{
		if (src[index] != target[index])
			return (b_false);
		index++;
	}
	return (b_true);
}
