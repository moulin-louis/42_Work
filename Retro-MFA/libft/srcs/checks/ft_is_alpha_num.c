/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_alpha_num.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 12:30:13 by ldutriez          #+#    #+#             */
/*   Updated: 2021/05/27 17:35:44 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_checks.h"

t_bool	ft_is_alpha_num(char c)
{
	if (ft_is_digit(c) == b_true || ft_is_alpha(c) == b_true)
		return (b_true);
	return (b_false);
}
