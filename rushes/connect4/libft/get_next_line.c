/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 07:07:22 by marnaudy          #+#    #+#             */
/*   Updated: 2022/02/16 11:53:30 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

static int	ft_line_size(t_buffer buffer)
{
	int		i;

	i = 0;
	while (buffer.idx + i < buffer.size)
	{
		if (buffer.content[buffer.idx + i] == '\n')
			return (i + 1);
		i++;
	}
	return (i);
}

static char	*ft_strcat_buffer(char *str, t_buffer *buffer, int n)
{
	char	*new;
	int		i;
	int		j;

	new = malloc(sizeof(char) * (ft_strlen(str) + n + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (str && str[i])
	{
		new[i] = str[i];
		i++;
	}
	free(str);
	j = 0;
	while (j < n)
	{
		new[i + j] = buffer->content[buffer->idx];
		j++;
		buffer->idx++;
	}
	new[i + j] = 0;
	return (new);
}

static void	ft_read_file(int fd, t_buffer *buffer)
{
	int	n;

	n = read(fd, buffer->content, BUFFER_SIZE);
	buffer->idx = 0;
	if (n < 0)
		n = 0;
	buffer->size = n;
}

static char	*ft_read_buffer(t_buffer *buffer, char *str)
{
	int	line_len;

	if (buffer->idx < buffer->size)
	{
		line_len = ft_line_size(*buffer);
		str = ft_strcat_buffer(str, buffer, line_len);
	}
	return (str);
}

char	*get_next_line(int fd)
{
	char			*str;
	static t_buffer	buffer;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (0);
	str = 0;
	while (1)
	{
		if (buffer.size == buffer.idx)
		{
			ft_read_file(fd, &buffer);
			if (buffer.size <= 0)
				return (str);
		}
		str = ft_read_buffer(&buffer, str);
		if (! str || (str && str[0] && str[ft_strlen(str) - 1] == '\n'))
			return (str);
	}
}
