/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:19:30 by loumouli          #+#    #+#             */
/*   Updated: 2022/02/23 12:40:15 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_is_sep(char c, char *sep)
{
	int	i;

	i = 0;
	while (sep[i])
	{
		if (sep[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_nbrstr(char *str, char *sep)
{
	int	i;
	int	nbrstr;

	i = 0;
	nbrstr = 0;
	while (ft_is_sep(str[i], sep))
		i++;
	while (str[i])
	{
		while (!(ft_is_sep(str[i], sep)) && str[i])
			i++;
		nbrstr++;
		while (ft_is_sep(str[i], sep) && str[i])
			i++;
	}
	return (nbrstr);
}

int	ft_strlen_sep(char *str, int index, char *sep)
{
	int	j;

	j = 0;
	while (str[index] && (!(ft_is_sep(str[index], sep))))
	{
		index++;
		j++;
	}
	return (j);
}

void	ft_cut_str(char *str, char *sep, char **dest)
{
	int	i;
	int	j;
	int	index;

	i = 0;
	j = 0;
	index = 0;
	while (str[i])
	{
		if (!(ft_is_sep(str[i], sep)) && str[i])
		{
			j = 0;
			dest[index] = malloc(((ft_strlen_sep(str, i, sep) + 1)
						* sizeof(char)));
			while (!(ft_is_sep(str[i], sep)) && str[i])
			{
				dest[index][j] = str[i];
				i++;
				j++;
			}
			dest[index][j] = 0;
			index++;
		}
		i++;
	}
}

char	**ft_split(char *str, char *charset)
{
	char	**dest;
	int		nbrstr;

	nbrstr = ft_nbrstr(str, charset);
	dest = malloc(((nbrstr) +1) * sizeof(char *));
	dest[nbrstr] = NULL;
	ft_cut_str(str, charset, dest);
	return (dest);
}
