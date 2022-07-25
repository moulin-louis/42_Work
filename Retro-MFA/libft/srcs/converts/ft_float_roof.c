/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_float_roof.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 13:11:18 by ldutriez          #+#    #+#             */
/*   Updated: 2021/05/28 03:53:12 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_converts.h"

float	ft_float_roof(float value)
{
	float	result;
	int		int_value;

	int_value = value;
	if (value == 0.0f)
		return (value);
	if (value < 0.0f)
	{
		result = int_value;
		return (result);
	}
	if (value - int_value == 0.0f)
	{
		result = value;
		return (result);
	}
	else
		result = int_value + 1;
	return (result);
}
