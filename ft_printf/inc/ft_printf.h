/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 14:08:34 by loumouli          #+#    #+#             */
/*   Updated: 2022/12/19 15:56:00 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdarg.h>

int	ft_printf(const char *str, ...);
int	ft_putchar_printf(char c);
int	ft_putnbr_base_printf(int nbr, char *base);
int	ft_putstr_printf(char *s);
int	ft_putnbr_printf(int nbr);
int	ft_putunbr_printf(unsigned int nb);
int	ft_print_adress_printf(unsigned long nbr, char *str);
int	ft_putnbr_long_printf(long nb);

#endif
