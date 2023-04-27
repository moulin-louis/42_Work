/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:00:06 by loumouli          #+#    #+#             */
/*   Updated: 2023/03/10 12:16:58 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include <cmath>

//CONSTRUCTOR AND DESTRUCTOR
//Default constructor
Fixed::Fixed ( void ) {
	std::cout << "Default Fixed constructor called" << std::endl;
	this->value = 0;
	return ;
}
//Constrcutor with an int
Fixed::Fixed( const int i ) {
	std::cout << "Int Fixed constructor called" << std::endl;

	this->value = i * (1 << this->nbr_fract_bits);
	return ;
}
//Constructor with an float
Fixed::Fixed( const float i) {
	std::cout << "Float Fixed constructor called" << std::endl;
	this->value = roundf(i * (1 << this->nbr_fract_bits));
	return ;
}
//Constructor with a Fixed instance as arg
Fixed::Fixed ( const Fixed& var) {
	std::cout << "Copy Fixed constructor by copy called" << std::endl;
	this->value = var.value;
	return ;
}
//Default destructor
Fixed::~Fixed ( void ) {
	std::cout << "Fixed destructor called" << std::endl;
	return ;
}


//OVERLOAD FUNCTION
//Overload of the = operator
Fixed& Fixed::operator=(const Fixed *var) {
	std::cout << "Fixed constructor by assignement operator called" << std::endl;
	this->value = var->value;
	return (*this);
}
//Overload of the << operator, display the value as a float on the outstream
std::ostream&	operator<<(std::ostream& os, const Fixed& var) {
	return os << var.toFloat();
}

//Return rawbits of the value as a int
int	Fixed::getRawBits( void ) {
	std::cout << "getRawBits called" << std::endl;
	return (this->value);
}
//Set the value to the arg
void	Fixed::setRawBits ( int const raw ) {
	this->value = raw;
}
//Return the value as a float
float	Fixed::toFloat( void ) const {
	return (this->value / (1 << this->nbr_fract_bits));
}
//Return the value as an int
int	Fixed::toInt( void ) const {
	return (this->value >> this->nbr_fract_bits);
}

