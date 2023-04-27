/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:00:04 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/20 13:41:19 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>

class Fixed
{
private:
	int	value;
	static	const	int	nbr_fract_bits = 8;
public:
	Fixed( void );
	Fixed ( const Fixed&);
	~Fixed();
	int		getRawBits( void );
	void	setRawBits( int const raw );
	Fixed	&operator=(const Fixed&);
};
