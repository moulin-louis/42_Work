/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_io.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 16:30:53 by ldutriez          #+#    #+#             */
/*   Updated: 2021/05/28 03:56:24 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_IO_H
# define LIBFT_IO_H

/*
**	Needed for size_t
*/
# include <stddef.h>

/*
**	Needed to use file related functions | syscall
*/
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>

/*
**	Needed by almost every functions
*/
# include "libft_strings.h"

/*
**	Printing a character.
*/
void			ft_putchar(char c);

/*
**	Printing a character in a file.
*/
void			ft_putchar_fd(int fd, char c);

/*
**	Printing a character in a file. The actual file is defined with
**	a path rathe than a file descriptor. Note that user can choose
**	3 modes to open the file (OVERWRITE, APPEND, CREATE). User also can
**	define a name for the array. Otherwise, set NULL as the second parameter.
*/
void			ft_putchar_fp(char *path, char c, char *mode);

/*
**	Printing a string.
*/
void			ft_putstr(char *str);

/*
**	Printing a string in a file.
*/
void			ft_putstr_fd(int fd, char *str);

/*
**	Printing a string in a file. The actual file
**	is defined with a path rather than a file descriptor.
*/
void			ft_putstr_fp(char *path, char *str, char *mode);

/*
**	Printing an integer value.
*/
void			ft_putnbr(int nb);

/*
**	Printing an integer value in a file.
*/
void			ft_putnbr_fd(int fd, int nb);

/*
**	Printing an integer value in a file. The actual file
**	is defined with a path rather than a file descriptor.
*/

void			ft_putnbr_fp(char *path, int nb, char *mode);

/*
**	Printing a 2 dimensions characters array. Note that user can
**	define a name for the array. Otherwise, set NULL as the second parameter.
*/
void			ft_print_str_tab(char *name, char **tab);

/*
**	Printing a 2 dimensions characters array in a file. Note that user can
**	define a name for the array. Otherwise, set NULL as the second parameter.
*/
void			ft_print_str_tab_fd(int fd, char *name, char **tab);

/*
**	Printing a 2 dimensions characters array in a file. The actual file is
**	defined with a path rathe than a file descriptor. Note that user can
**	choose 3 modes to open the file (OVERWRITE, APPEND, CREATE). User also can
**	define a name for the array. Otherwise, set NULL as the second parameter.
*/
void			ft_print_str_tab_fp(char *path,
					char *name, char **tab, char *mode);

/*
**	Printing a 2 dimensions integers array. Note that user can
**	define a name for the array. Otherwise, set NULL as the second parameter.
*/
void			ft_print_int_tab(char *name, int *tab, size_t len);

/*
**	Printing a 2 dimensions integers array in a file. Note that user can
**	define a name for the array. Otherwise, set NULL as the second parameter.
*/
void			ft_print_int_tab_fd(int fd,
					char *name, int *tab, size_t len);

#endif
