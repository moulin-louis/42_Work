/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 11:17:04 by loumouli          #+#    #+#             */
/*   Updated: 2022/09/16 17:20:06 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	return (free(buff), buffer_saved);s

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
