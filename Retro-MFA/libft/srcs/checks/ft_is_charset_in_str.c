/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_charset_in_str.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notcampeur <notcampeur@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 15:14:11 by ncoudsi           #+#    #+#             */
/*   Updated: 2021/10/04 15:16:38 by notcampeur       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_checks.h"

/*
**	Checking if charset string contain to_find character. Returns b_true at the
**	first occurence, b_false if none is found.
*/

static t_bool	is_in_charset(char to_find, char *charset)
{
	int	index;

	index = 0;
	while (charset[index] != '\0')
	{
		if (charset[index] == to_find)
			return (b_true);
		index++;
	}
	return (b_false);
}

t_bool	ft_is_charset_in_str(char *str, char *to_find)
{
	size_t	index;

	index = 0;
	if (str == NULL || to_find == NULL)
		return (0);
	while (str[index] != '\0')
	{
		if (is_in_charset(str[index], to_find) == b_true)
			return (b_true);
		index++;
	}
	return (b_false);
}
