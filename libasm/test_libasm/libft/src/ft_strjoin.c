/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:36:16 by loumouli          #+#    #+#             */
/*   Updated: 2022/05/04 13:00:36 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*libft_ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	int		i;
	int		j;

	result = malloc(sizeof(char) * ((libft_ft_strlen(s1) + libft_ft_strlen(s2)) + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		result[j] = s1[i];
		i++;
		j++;
	}
	i = 0;
	while (s2[i])
	{
		result [j] = s2[i];
		i++;
		j++;
	}
	result[j] = '\0';
	return (result);
}
