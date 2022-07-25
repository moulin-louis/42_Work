/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_char_in_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 11:22:56 by ncoudsi           #+#    #+#             */
/*   Updated: 2021/05/28 03:51:20 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_checks.h"

t_bool	is_char_in_str(char to_find, char *str)
{
	int	index;

	index = 0 ;
	while (str[index] != '\0')
	{
		if (str[index] == to_find)
			return (b_true);
		index++;
	}
	return (b_false);
}
