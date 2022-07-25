/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str_tab_fp.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 14:49:30 by ncoudsi           #+#    #+#             */
/*   Updated: 2021/05/28 03:56:20 by user42           ###   ########.fr       */
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

/*
**	Printing the actual array.
*/
static void	print_tab(int fd, char *name, char **tab)
{
	size_t	index;

	index = 0;
	if (name != NULL)
	{
		ft_putchar_fd(fd, '{');
		ft_putstr_fd(fd, name);
		ft_putstr_fd(fd, "}\n");
	}
	ft_putstr_fd(fd, "-----===-----\n");
	while (tab && tab[index])
	{
		ft_putnbr_fd(fd, index);
		ft_putstr_fd(fd, "--->[");
		ft_putstr_fd(fd, tab[index]);
		ft_putstr_fd(fd, "]\n");
		index++;
	}
	ft_putstr_fd(fd, "-----===-----\n");
}

void	ft_print_str_tab_fp(char *path,
			char *name, char **tab, char *mode)
{
	int	fd;

	fd = -1;
	if (mode == NULL || path == NULL)
		return ;
	if (ft_strcmp(mode, "OVERWRITE") == b_true)
		fd = file_overwrite(path);
	else if (ft_strcmp(mode, "APPEND") == b_true)
		fd = file_append(path);
	else if (ft_strcmp(mode, "CREATE") == b_true)
		fd = file_create(path);
	if (fd == -1)
	{
		ft_putstr_fd(2, "Invalid file path in ft_print_str_tab_fp().\n");
		return ;
	}
	print_tab(fd, name, tab);
	close(fd);
}
