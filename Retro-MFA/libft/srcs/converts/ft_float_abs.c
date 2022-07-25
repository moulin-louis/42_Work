/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_float_abs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 09:03:19 by ldutriez          #+#    #+#             */
/*   Updated: 2021/05/27 17:24:46 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_converts.h"

float	ft_float_abs(float value)
{
	if (value == 0.0f)
		return (0.0f);
	if (value < 0.0f)
		value *= -1;
	return (value);
}
