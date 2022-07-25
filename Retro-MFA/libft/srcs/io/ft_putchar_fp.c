/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 15:03:39 by ncoudsi           #+#    #+#             */
/*   Updated: 2021/05/28 03:56:44 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_io.h"
#include "libft_checks.h"

/*
**	The 3 static functions bellow open the file with specific mode.
*/

static int	file_overwrite(char *path)
{
	int	fd;

	fd = open(path, O_WRONLY | O_TRUNC);
	return (fd);
}

static int	file_append(char *path)
{
	int	fd;

	fd = open(path, O_WRONLY | O_APPEND);
	return (fd);
}

static int	file_create(char *path)
{
	int	fd;

	fd = open(path, O_WRONLY | O_APPEND | O_CREAT, 00700);
	return (fd);
}

void	ft_putchar_fp(char *path, char c, char *mode)
{
	int	fd;

	fd = -1;
	if (path == NULL || mode == NULL || path == NULL)
		return ;
	if (ft_strcmp(mode, "OVERWRITE"))
		fd = file_overwrite(path);
	else if (ft_strcmp(mode, "APPEND"))
		fd = file_append(path);
	else if (ft_strcmp(mode, "CREATE"))
		fd = file_create(path);
	if (fd == -1)
	{
		ft_putstr_fd(2, "Invalid file path in ft_print_str_tab_fp().\n");
		return ;
	}
	write(fd, &c, 1);
	close(fd);
}
