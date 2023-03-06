/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 12:14:33 by mpignet           #+#    #+#             */
/*   Updated: 2023/03/06 18:07:57 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	allign_ptr(const char **char_ptr, char *str)
{
	unsigned long int		longword;

	*char_ptr = str;
	while (((unsigned long int) *char_ptr & (sizeof(longword) - 1)) != 0)
	{
		++*char_ptr;
		if (**char_ptr == '\0')
			return (1);
	}
	return (0);
}

void	init_word_magic(unsigned long *longword,
		unsigned long *himagic, unsigned long *lomagic)
{
	*himagic = 0x80808080L;
	*lomagic = 0x01010101L;
	if (sizeof (*longword) > 4)
	{
		*himagic = ((*himagic << 16) << 16) | *himagic;
		*lomagic = ((*lomagic << 16) << 16) | *lomagic;
	}
	if (sizeof (longword) > 8)
		exit(0);
}

int	search_zero(unsigned long int *offset,
		const char *char_ptr, unsigned long int longword)
{
	if (char_ptr[0] == 0)
		return (*offset = 0, 1);
	if (char_ptr[1] == 0)
		return (*offset = 1, 1);
	if (char_ptr[2] == 0)
		return (*offset = 2, 1);
	if (char_ptr[3] == 0)
		return (*offset = 3, 1);
	if (sizeof(longword) > 4)
	{
		if (char_ptr[4] == 0)
			return (*offset = 4, 1);
		if (char_ptr[5] == 0)
			return (*offset = 5, 1);
		if (char_ptr[6] == 0)
			return (*offset = 6, 1);
		if (char_ptr[7] == 0)
			return (*offset = 7, 1);
	}
	return (0);
}

size_t	ft_strlen(const char *str)
{
	const char				*char_ptr;
	const unsigned long int	*longword_ptr;
	unsigned long int		stuff[4];

	char_ptr = NULL;
	stuff[3] = 0;
	if (allign_ptr(&char_ptr, (char *)str) == 1)
		return (char_ptr - str);
	longword_ptr = (unsigned long int *) char_ptr;
	init_word_magic(&stuff[0], &stuff[1], &stuff[2]);
	while (1)
	{
		stuff[0] = *longword_ptr++;
		if (((stuff[0] - stuff[2]) & ~stuff[0] & stuff[1]) != 0)
		{
			char_ptr = (const char *)(longword_ptr - 1);
			if (search_zero(&stuff[3], char_ptr, stuff[0]) == 1)
				return (char_ptr - str + stuff[3]);
		}
	}
}
