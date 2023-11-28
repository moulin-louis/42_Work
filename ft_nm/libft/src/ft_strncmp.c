/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 18:12:00 by loumouli          #+#    #+#             */
/*   Updated: 2022/05/04 12:50:00 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((s1[i] == s2[i]) && s1[i] != 0 && s2[i] != 0 && i < n -1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int ft_strcmp (const char *p1, const char *p2) {
	register const unsigned char *s1 = (const unsigned char *) p1;
	register const unsigned char *s2 = (const unsigned char *) p2;
	unsigned char c1, c2;

	do
	{
		c1 = (unsigned char) *s1++;
		c2 = (unsigned char) *s2++;
		if (c1 == '\0')
			return c1 - c2;
	}
	while (c1 == c2);

	return c1 - c2;
}

int	ft_strncmp_map(const char *s1, const char *s2, size_t n, char (*map)(char)) {
	unsigned int	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((map(s1[i]) == map(s2[i])) && map(s1[i]) != 0 && map(s2[i]) != 0 && i < n -1)
		i++;
	return (map(s1[i]) - map(s2[i]));
}