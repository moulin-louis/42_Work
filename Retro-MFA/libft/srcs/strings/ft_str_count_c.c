/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_count_c.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 10:55:11 by ncoudsi           #+#    #+#             */
/*   Updated: 2021/05/27 17:33:15 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_strings.h"

int	ft_str_count_c(char *str, char c)
{
	int	result;
	int	index;

	result = 0;
	index = 0;
	while (str[index] != '\0')
	{
		if (str[index] == c)
			result++;
		index++;
	}
	return (result);
}
