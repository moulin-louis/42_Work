/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 18:07:26 by loumouli          #+#    #+#             */
/*   Updated: 2023/02/12 15:29:44 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static	int	ft_nbr_str(char *s, char c)
{
	int	nbr_str;
	int	i;

	nbr_str = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			while (s[i] != c && s[i])
				i++;
			nbr_str++;
		}
	}
	return (nbr_str);
}

static	int	ft_str_len_char(char *s, int i, char c)
{
	int	a;

	a = 0;
	while (s[i] != c && s[i])
	{
		a++;
		i++;
	}
	return (a);
}

static	int	ft_fill_string(char *dest, char *src, int index, char sep)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (src[index] != sep && src[index])
	{
		dest[j] = src[index];
		j++;
		i++;
		index++;
	}
	dest[j] = '\0';
	return (i);
}

static	void	ft_fil_result(char *s, char **result, char c)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (s[i] == c && s[i])
		i++;
	while (s[i])
	{
		if (s[i] != c)
		{
			result[x] = malloc(sizeof(char) * (ft_str_len_char(s, i, c) + 1));
			if (!result[x])
				return ;
			i = i + ft_fill_string(result[x], s, i, c);
			x++;
		}
		if (s[i] == 0)
			break ;
		i++;
	}
}

/* Si ca return NULL car malloc fail,
leak car je ne free pas les malloc precedent.
A faire attention pour les prochains projets*/

char	**libft_ft_split(char const *s, char c)
{
	int		nbr_str;
	char	**result;

	nbr_str = ft_nbr_str((char *)s, c);
	result = malloc(sizeof(char *) * (nbr_str + 1));
	if (!result)
		return (NULL);
	ft_fil_result((char *)s, result, c);
	result[nbr_str] = NULL;
	return (result);
}
