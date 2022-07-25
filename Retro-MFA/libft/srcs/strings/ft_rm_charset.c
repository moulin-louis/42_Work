/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rm_charset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 18:59:06 by ldutriez          #+#    #+#             */
/*   Updated: 2021/05/28 04:00:34 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_strings.h"
#include "libft_checks.h"

/*
**	Counting the lenght of the string without the characters of
**	the charset and returning it.
*/
static int	len_without_charset(char *str, char *charset)
{
	int	result;
	int	index;

	result = 0;
	index = 0;
	if (str == NULL)
		return (result);
	while (str[index] != '\0')
	{
		if (is_char_in_str(str[index], charset) == b_false)
			result++;
		index++;
	}
	return (result);
}

char	*ft_rm_charset(char *str, char *charset)
{
	char	*result;
	int		index;
	int		result_index;

	if (str == NULL)
		return (NULL);
	index = 0;
	result_index = 0;
	result = ft_strnew(len_without_charset(str, charset));
	if (result == NULL)
		return (NULL);
	while (str[index] != '\0')
	{
		if (is_char_in_str(str[index], charset) == b_false)
		{
			result[result_index] = str[index];
			result_index++;
		}
		index++;
	}
	free(str);
	return (result);
}
