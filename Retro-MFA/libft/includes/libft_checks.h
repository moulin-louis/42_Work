/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_checks.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 16:28:36 by ldutriez          #+#    #+#             */
/*   Updated: 2021/05/28 03:31:58 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_CHECKS_H
# define LIBFT_CHECKS_H

/*
**	Needed to use t_bool
*/
# include "libft_enums.h"

/*
**	Needed to use file related functions | syscall
*/
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>

/*
**	Checking if str string contains at least one char
**	Return true at the first occurence, return false if none is found.
*/
t_bool			is_char_in_str(char to_find, char *str);

/*
**	Checking in a string if all the characters are digits.
*/
t_bool			ft_is_only_digits(char *str);

/*
** Checking if a character is numeric.
*/
t_bool			ft_is_digit(char c);

/*
**	Cheking if 2 strings are entirely similar.
*/
t_bool			ft_strcmp(char *src, char *target);

/*
**	Checking if str string contains at least one character of the to_find
**	string. Return true at the first occurence, return false if none is found.
*/
t_bool			ft_is_charset_in_str(char *str, char *to_find);

/*
**	Cheking if a character is a white space.
*/
t_bool			ft_is_white_space(char c);

/*
**	Checking if a character is an upper case alphabetic.
*/
t_bool			ft_is_upper(char c);

/*
**	Checking if a character is a lower case alphabetic.
*/
t_bool			ft_is_lower(char c);

/*
**	Checking if a character is alphabetic, upper or lower case.
*/
t_bool			ft_is_alpha(char c);

/*
**	Checking if a character is rather numeric or alphabetic.
*/
t_bool			ft_is_alpha_num(char c);

/*
**	Checking if the path of the file is valid by opening it and verifying
**	open() 's return.
*/
t_bool			ft_is_valid_file_path(char *path);

#endif
