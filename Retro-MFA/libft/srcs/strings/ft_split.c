/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 10:57:07 by ncoudsi           #+#    #+#             */
/*   Updated: 2021/05/28 04:03:31 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_strings.h"
#include "libft_tabs.h"

/*
**	Counting how many words we have after splitting the initial string.
*/

static size_t	word_count(char *src, char sep)
{
	size_t	index;
	size_t	result;

	index = 0;
	result = 0;
	while (src[index] != '\0')
	{
		if (src[index] == sep)
			index++;
		if (src[index] != '\0' && src[index] != sep)
		{
			result++;
			while (src[index] != '\0' && src[index] != sep)
				index++;
		}
	}
	return (result);
}

/*
**	In case of error, free everything.
*/

static void	clear(char **tab, int tab_index)
{
	while (tab_index >= 0)
	{
		free(tab[tab_index]);
		tab_index--;
	}
	free(tab);
}

/*
**	Counting the size of a word, wich is ended whenever we encounter
**	a separator.
*/

static size_t	word_len(char *src, char sep)
{
	size_t	result;

	result = 0;
	while (src[result] != '\0' && src[result] != sep)
		result++;
	return (result);
}

/*
**	Filling the char ** containing the splitted strings.
*/

static void	fill_tab(char **tab, char *src,
				char sep, size_t tab_size)
{
	size_t	index;
	size_t	tab_index;

	index = 0;
	tab_index = 0;
	while (tab_index < tab_size)
	{
		while (src[index] != '\0' && src[index] == sep)
			index++;
		if (src[index] != '\0')
		{
			tab[tab_index] = ft_strsub(src, index,
					word_len(src + index, sep));
			if (tab[tab_index] == NULL)
			{
				clear(tab, tab_index);
				return ;
			}
		}
		while (src[index] != '\0' && src[index] != sep)
			index++;
		tab_index++;
	}
	tab[tab_index] = NULL;
}

char	**ft_split(char *src, char sep)
{
	size_t	tab_size;
	char	**result;

	if (src == NULL || sep == '\0')
		return (NULL);
	tab_size = word_count(src, sep);
	result = (char **)ft_tab_new(tab_size);
	if (result == NULL)
		return (NULL);
	fill_tab(result, src, sep, tab_size);
	if (result == NULL)
		return (NULL);
	return (result);
}
