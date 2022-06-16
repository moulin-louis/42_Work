/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 11:50:39 by loumouli          #+#    #+#             */
/*   Updated: 2022/06/15 14:15:09 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int	get_nbr_line(char **result)
{
	int	x;

	x = 0;
	while (result[x])
		x++;
	return (x);
}

int	fill_map(t_data *data)
{
	int		fd;
	char	*buff;
	int x;

	fd = open(PATH_MAP, O_RDONLY);
	if (fd == -1)
		return (-5);
	buff = malloc(sizeof(char) * 100000);
	if (!buff)
		return (-5);
	x = read(fd, buff, 100000);
	buff[x - 1] = '\0';
	data->map  = ft_split(buff, '\n');
	if (data->map == NULL)
		return (-5);
	return (free (buff), close (fd), get_nbr_line(data->map));
}

int	check_map(int nbr_line, char **map)
{
	int	x;
	int	j;

	if (nbr_line == -5)
		return (-5);
	x = 1;
	j = 0;
	while (map[0][j])
	{
		if (map[0][j] != '1')
			return (-5);
		j++;
	}
	j = 0;
	while (map[nbr_line -1][j])
	{
		if (map[0][j] != '1')
			return (-5);
		j++;
	}
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

int	setup_map(t_data *data)
{
	int nbr_line;

	nbr_line = fill_map(data);
	if (check_square(data->map) == -5)
		return (destroy_double_array(data), -1);
	if (check_map(nbr_line, data->map) == -5)
		return (destroy_double_array(data), -1);
	return (1);
}
