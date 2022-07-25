/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_float_round.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 18:54:18 by tguilbar          #+#    #+#             */
/*   Updated: 2021/05/27 17:24:59 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_converts.h"

float	ft_float_round(float value)
{
	float	floor;
	float	roof;

	floor = ft_float_floor(value);
	roof = ft_float_roof(value);
	if ((value - floor) < (roof - value))
		return (floor);
	else
		return (roof);
}
