/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 11:52:39 by loumouli          #+#    #+#             */
/*   Updated: 2022/06/03 12:23:49 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	if (c > 0)
		c = (char)c;
	if (c == '\0')
	{
		while (*s)
			s++;
		return ((char *) s);
	}
	while (*s)
	{
		if (*s == c)
			return ((char *) s);
		s++;
	}
	return (0);
}

int	ft_strlen(char *str)
{
	int	x;

	x = 0;
	while (str[x])
		x++;
	return (x);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		len;
	char	*result;
	int		i;

	i = -1;
	if (!s1)
	{
		s1 = malloc(BUFFER_SIZE * sizeof(char));
		if (!s1)
			return (free (s2), NULL);
		s1[0] = '\0';
	}
	len = ft_strlen(s1) + ft_strlen(s2);
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (free(s1), free(s2), NULL);
	while (s1[++i])
		result[i] = s1[i];
	while (*s2)
		result[i++] = *s2++;
	return (result[len] = '\0', free (s1), result);
}
