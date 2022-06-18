/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 11:30:18 by marnaudy          #+#    #+#             */
/*   Updated: 2021/11/24 15:16:16 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_nb_string(char const *s, char c)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			nb++;
			while (s[i] && s[i] != c)
				i++;
			i--;
		}
		i++;
	}
	return (nb);
}

static char	**ft_check_array(char **array, int size)
{
	int	i;
	int	is_good;

	i = 0;
	is_good = 1;
	while (i < size)
	{
		is_good = (is_good && array[i]);
		i++;
	}
	if (is_good)
		return (array);
	i = 0;
	while (i < size)
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		arr_idx;
	char	**array;

	array = malloc(sizeof(char *) * (ft_nb_string(s, c) + 1));
	if (!array)
		return (NULL);
	i = 0;
	arr_idx = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			j = 0;
			while (s[i + j] != c && s[i + j])
				j++;
			array[arr_idx++] = ft_substr(s, i, j);
			i += j - 1;
		}
		i++;
	}
	array[arr_idx] = NULL;
	return (ft_check_array(array, ft_nb_string(s, c)));
}
