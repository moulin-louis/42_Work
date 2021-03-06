/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_white_space.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 12:14:14 by ldutriez          #+#    #+#             */
/*   Updated: 2021/05/28 03:52:27 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_checks.h"

t_bool	ft_is_white_space(char c)
{
	if (c == '\t' || c == '\v' || c == '\n' || c == '\r'
		|| c == '\f' || c == ' ')
		return (b_true);
	return (b_false);
}
