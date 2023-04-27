/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:00:06 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/19 18:01:58 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

Fixed::Fixed ( void )
{
	std::cout << "Fixed constructor called" << std::endl;
	this->value = 0;
	return ;
}

Fixed::Fixed ( const Fixed& var)
{
	std::cout << "Fixed constructor by copy called" << std::endl;
	this->value = var.value;
	return ;
}

Fixed::~Fixed ( void )
{
	std::cout << "Fixed destructor called" << std::endl;
	return ;
}

int	Fixed::getRawBits( void )
{
	std::cout << "getRawBits called" << std::endl;
	return (this->value);
}

void	Fixed::setRawBits ( int const raw )
{
	this->value = raw;
}

Fixed& Fixed::operator=(const Fixed&)
{
	std::cout << "Fixed constructor by assignement operator called" << std::endl;
	return (*this);
}