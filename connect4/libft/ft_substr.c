/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 11:23:37 by marnaudy          #+#    #+#             */
/*   Updated: 2021/11/24 12:31:45 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static unsigned int	ft_substr_len(char const *s, unsigned int start, size_t len)
{
	int	max_len;

	max_len = ft_strlen(s) - start;
	if (max_len < 0)
		max_len = 0;
	if (max_len < (int) len)
		return (max_len);
	return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*new;

	new = malloc(sizeof(char) * (ft_substr_len(s, start, len) + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (s[i] && i < start)
		i++;
	if (!s[i])
	{
		new[0] = 0;
		return (new);
	}
	i = 0;
	while (s[start + i] && i < len)
	{
		new[i] = s[start + i];
		i++;
	}
	new[i] = 0;
	return (new);
}
