/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_float_floor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 08:54:40 by ldutriez          #+#    #+#             */
/*   Updated: 2021/05/27 17:24:50 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_converts.h"

float	ft_float_floor(float value)
{
	int		int_value;
	float	result;

	int_value = (int)value;
	result = int_value;
	return (result);
}
