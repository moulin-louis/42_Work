/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_files.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 16:16:15 by ldutriez          #+#    #+#             */
/*   Updated: 2022/05/26 17:45:14 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_FILES_H
# define LIBFT_FILES_H

/*
**	Needed to use file related functions | syscall
*/
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>

/*
**	Needed to use malloc/free | size_t
*/
# include <stdlib.h>

/*
**	Needed by almost every functions
*/
# include "libft_strings.h"

/*
**	Needed by ft_get_file_in_list
*/
# include "libft_lists.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

# define IS_NOT_A_LINE 2
# define IS_A_LINE 1
# define IS_END_OF_FILE 0
# define IS_AN_ERROR -1

/*
**	Getting the next line of a file and store it in a string. We consider a line
**	as an undefined number of characters terminated with '\n'. The function
**	returns 1 if a line has been found, 0 if the enf of file has beem reached
**	and -1 if an error occured.
*/
int				get_next_line(int fd, char **line);

/*
**	Opening a file and getting its datas line by line. Storing it in a char **
**	and returning it. If the path to the file is incorrect, returning NULL.
*/
char			**ft_get_file(char *path);

/*
**	Opening a file and getting its datas line by line.
**	Storing it in a double linked list and returning it.
**	If the path to the file is incorrect, returning NULL.
*/
t_d_list		ft_get_file_in_list(char *path);

#endif
