/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 11:50:39 by loumouli          #+#    #+#             */
/*   Updated: 2022/06/18 09:09:53 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int	fill_map(t_data *data, char *path)
{
	int		fd;
	char	*buff;
	int		x;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (-5);
	buff = malloc(sizeof(char) * 100000);
	if (!buff)
		return (-5);
	x = read(fd, buff, 100000);
	if (x == -1)
		return (-5);
	buff[x - 1] = '\0';
	data->map = ft_split(buff, '\n');
	if (data->map == NULL)
		return (-5);
	x = 0;
	while (data->map[x])
		x++;
	return (free (buff), close (fd), x);
}

int	ft_check_first_last_line(char **map, int nbr_line)
{
	int	j;

	j = 0;
	while (map[0][j])
	{
		if (map[0][j] != '1')
			return (-5);
		j++;
	}
	j = 0;
	while (map[nbr_line - 1][j])
	{
		if (map[nbr_line - 1][j] != '1')
			return (-5);
		j++;
	}
	return (1);
}

int	check_map(int nbr_line, char **map)
{
	int	x;

	if (nbr_line == -5)
		return (-5);
	x = 1;
	if (ft_check_first_last_line(map, nbr_line) == -5)
		return (-5);
	while (x < nbr_line - 2)
	{
		if (map[x][0] != '1' || map[x][ft_strlen(map[x]) - 1] != '1')
			return (-5);
		x++;
	}
	return (1);
}

int	check_square(char **map)
{
	int	x;

	x = 0;
	while (map[x])
	{
		if (map[x + 1] == NULL)
		{
			x++;
			continue ;
		}
		if (ft_strlen(map[x]) != ft_strlen(map[x + 1]))
			return (-5);
		x++;
	}
	return (1);
}

int	setup_map(t_data *data, char *path)
{
	int	nbr_line;

	nbr_line = fill_map(data, path);
	if (nbr_line == -5)
		return (-1);
	if (check_square(data->map) == -5)
		return (destroy_double_array(data), -1);
	if (check_map(nbr_line, data->map) == -5)
		return (destroy_double_array(data), -1);
	data->width = ft_strlen(data->map[0]) * 32;
	nbr_line = 0;
	while (data->map[nbr_line])
		nbr_line++;
	data->height = nbr_line * 32;
	return (1);
}
