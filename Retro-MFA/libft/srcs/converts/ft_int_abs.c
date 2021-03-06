/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_abs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 09:00:01 by ldutriez          #+#    #+#             */
/*   Updated: 2021/05/28 03:53:29 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_converts.h"

int	ft_int_abs(int value)
{
	if (value == 0)
		return (0);
	if (value < 0)
		value *= -1;
	return (value);
}
