/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 11:52:31 by loumouli          #+#    #+#             */
/*   Updated: 2022/06/03 13:15:54 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_fill_save(char *buffer_saved, int fd)
{
	char	*buff;
	int		nbr_char_read;

	buff = malloc(sizeof(char) * (BUFFER_SIZE + 2));
	if (!buff)
		return (NULL);
	buff[0] = '\0';
	nbr_char_read = 1;
	while (nbr_char_read && !(ft_strchr(buff, '\n')))
	{
		nbr_char_read = read(fd, buff, BUFFER_SIZE);
		if (nbr_char_read == -1)
			return (free(buff), free(buffer_saved), NULL);
		if (nbr_char_read)
		{
			buff[nbr_char_read] = '\0';
			buffer_saved = ft_strjoin(buffer_saved, buff);
		}
	}
	return (free(buff), buffer_saved);
}

char	*ft_fill_result(char *buffer_saved)
{
	int		len;
	char	*result_line;
	int		x;

	len = 0;
	x = 0;
	while (buffer_saved[len] && buffer_saved[len] != '\n')
		len++;
	len++;
	result_line = malloc(sizeof(char) * (len + 1));
	if (!result_line)
		return (NULL);
	if (buffer_saved[0] == '\0')
		return (free(result_line), NULL);
	while (x < len)
	{
		result_line[x] = buffer_saved[x];
		x++;
	}
	return (result_line[x] = '\0', result_line);
}

char	*ft_del_line(char *buffer_saved)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	while (buffer_saved[i] && buffer_saved[i] != '\n')
		i++;
	if (!buffer_saved[i])
		return (free(buffer_saved), NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(buffer_saved) - i + 1));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (buffer_saved[i])
		str[j++] = buffer_saved[i++];
	return (free(buffer_saved), str[j] = '\0', str);
}

char	*get_next_line(int fd)
{
	static char	*buffer_saved;
	char		*result_line;

	if (fd <= -1 || fd >= 1024 || BUFFER_SIZE < 0)
		return (NULL);
	buffer_saved = ft_fill_save(buffer_saved, fd);
	if (!buffer_saved)
		return (NULL);
	result_line = ft_fill_result(buffer_saved);
	return (buffer_saved = ft_del_line(buffer_saved), result_line);
}
