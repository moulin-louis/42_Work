/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_converts.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 16:29:47 by ldutriez          #+#    #+#             */
/*   Updated: 2021/05/28 03:50:17 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_CONVERTS_H
# define LIBFT_CONVERTS_H

/*
**	Needed for size_t
*/
# include <stddef.h>

/*
**	Rounding up a floating point value.
*/
float			ft_float_roof(float value);

/*
**	Casting a floating point value into an integer to round it down, then
**	returning the rounded floating point value.
*/
float			ft_float_floor(float value);

/*
**	Returning a rounded value of a floating point.
*/
float			ft_float_round(float value);

/*
**	Returning an absolute value of an integer.
*/
int				ft_int_abs(int value);

/*
**	Returning the absolute value of a floating point.
*/
float			ft_float_abs(float value);

/*
**	Converting an integer value into a string filled with numerical characters
**	refering to the value, in a set base.
*/
char			*ft_itoa_base(long long int nbr, char *base);

/*
**	Converting an integer value into a string filled with numerical characters
**	refering to the value.
*/
char			*ft_itoa(long long int nbr);

/*
**	Converting an integer value into a string filled with numerical characters
**	refering to the value, in an hexadecimal base.
*/
char			*ft_itoa_hexa(long long int nbr);

/*
**	Converting an integer value into a string filled with numerical characters
**	refering to the value, in an octadecimal base.
*/
char			*ft_itoa_octa(long long int nbr);

/*
**	Converting numericals characters in a string into an integer. Skip all the
**	spaces at the start of the string and accept one sign ('+' or '-'), then
**	take only numericals characters. As soon as we encounter a non numerical
**	character, we retrun the actual value of result.
*/
int				ft_atoi(char *str);

#endif
