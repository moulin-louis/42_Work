/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 18:07:26 by loumouli          #+#    #+#             */
/*   Updated: 2022/09/07 18:16:52 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_nb_words(char const *s, char c)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || !s[i + 1]))
			nb++;
		i++;
	}
	return (nb);
}

int	ft_len(char const *s, char c, size_t i)
{
	int	len;

	len = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (len);
		i++;
		len++;
	}
	return (len);
}

void	ft_free_all(char **tab, int x)
{
	int	i;

	i = 0;
	while (tab[i] && i < x)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	ft_fill(char **dest, char const *s, char c)
{
	size_t	i;
	size_t	x;
	size_t	len;

	i = 0;
	x = 0;
	while (s[i])
	{
		len = 0;
		if (s[i] != c)
		{
			len = ft_len(s, c, i);
			dest[x] = ft_substr(s, i, len);
			if (!dest[x])
			{
				ft_free_all(dest, x);
				return 1;
			}
			x++;
			i += len;
		}
		else
			i += len + 1;
	}
	return 0;
}

char	**ft_split(char const *s, char c)
{
	char	**dest;
	int		nb;

	if (!s)
		return (NULL);
	nb = ft_nb_words(s, c);
	dest = malloc (sizeof(char *) * (nb + 1));
	if (!dest)
		return (NULL);
	dest[nb] = NULL;
	if (ft_fill(dest, s, c) == 1)
		return (printf("ft_fill as returned 1\n"), NULL);
	return (dest);
}
