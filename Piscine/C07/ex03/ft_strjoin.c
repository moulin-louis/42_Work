/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 12:41:53 by loumouli          #+#    #+#             */
/*   Updated: 2022/02/22 11:21:38 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}

char	*ft_join_str(char *dest, char **strs, char *sep, int size)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	while (i < size)
	{
		ft_strcpy(dest + j, strs[i]);
		j += ft_strlen(strs[i]);
		if (i < size - 1)
		{
			ft_strcpy(dest + j, sep);
			j += ft_strlen(sep);
		}
		i++;
	}
	dest[j] = 0;
	return (dest);
}

char	*ft_strjoin(int size, char **strs, char *sep)
{
	int		i;
	int		j;
	char	*dest;

	i = 0;
	j = 0;
	while (i < size)
		j += ft_strlen(strs[i++]);
	if (size > 0)
		j += (size - 1) * ft_strlen(sep);
	dest = malloc((j + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	ft_join_str(dest, strs, sep, size);
	return (dest);
}
