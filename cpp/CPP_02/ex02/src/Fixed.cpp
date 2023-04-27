/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:00:06 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/20 13:44:58 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

//CONSTRUCTOR AND DESTRUCTOR
	//Default constructor
	Fixed::Fixed ( void ) {
		//std::cout << "Default Fixed constructor called" << std::endl;
		this->value = 0;
		return ;
	}
	//Constrcutor with an int
	Fixed::Fixed( const int i ) {
		//std::cout << "Int Fixed constructor called" << std::endl;
		this->value = i * (1 << this->nbr_fract_bits);
		return ;
	}
	//Constructor with an float
	Fixed::Fixed( const double i) {
	std::cout << "Float Fixed constructor called" << std::endl;
	this->value = roundf(i * (1 << this->nbr_fract_bits));
	return ;
	}
	//Constructor with a Fixed instance as arg
	Fixed::Fixed ( const Fixed& var) {
		//std::cout << "Copy Fixed constructor by copy called" << std::endl;
		this->value = var.value;
		return ;
	}
	//Default destructor
	Fixed::~Fixed ( void ) {
		//std::cout << "Fixed destructor called" << std::endl;
		return ;
	}

//OVERLOAD FUNCTION
	//Overload of the = operator
	Fixed& Fixed::operator=(const Fixed *var) {
		//std::cout << "Fixed constructor by assignement operator called" << std::endl;
		this->value = var->value;
		return (*this);
	}
	//Overload of the << operator, display the value as a float on the outstream
	std::ostream&	operator<<(std::ostream& os, const Fixed& var) {
		return os << var.toFloat();
	}
	//Overload of < operator
	bool	Fixed::operator<(const Fixed& var) {
		if (this->value < var.value)
			return (true);
		return (false);
	}
	//Overload of > operator
	bool	Fixed::operator>(const Fixed& var) {
		if (this->value > var.value)
			return (true);
		return (false);
	}
	//Overload of <= operator
	bool	Fixed::operator<=(const Fixed& var) {
		if (this->value <= var.value)
			return (true);
		return (false);
	}
	//Overload of >= operator
	bool	Fixed::operator>=(const Fixed& var) {
		if (this->value >= var.value)
			return (true);
		return (false);
	}
	//Overload of == operator
	bool	Fixed::operator==(const Fixed& var) {
		if (this->value == var.value)
			return (true);
		return (false);
	}
	//Overload of != operator
	bool	Fixed::operator!=(const Fixed& var) {
		if (this->value != var.value)
			return (true);
		return (false);
	}
	//Overload of + operator
	Fixed&	Fixed::operator+(const Fixed& var) {
		this->value = this->value + var.value;
		return (*this);
	}
	//Overload of - operator
	Fixed&	Fixed::operator-(const Fixed& var) {
		this->value = this->value - var.value;
		return (*this);
	}
	//Overload of * operator
	Fixed&	Fixed::operator*(const Fixed& var) {
		double	temp1 = this->toFloat();
		double	temp2 = var.toFloat();
		this->value = (temp1 * temp2 * (1 << this->nbr_fract_bits));
		return (*this);
	}
	//Overload of / operator
	Fixed&	Fixed::operator/(const Fixed& var) {
		this->value = this->value / var.value;
		return (*this);
	}
	//Overload of pre ++ increment
	Fixed&	Fixed::operator++() {
		value++;
		return (*this);
	}
	//Overloard of post ++ increment
	Fixed	Fixed::operator++ ( int ) {
		Fixed temp = *this;
		++*this;
		return (temp);
	}
	//Overload of  -- pre drecremnt
	Fixed&	Fixed::operator--() {
		value--;
		return (*this);
	}
	//Overload of  -- post drecremnt
	Fixed	Fixed::operator--( int ) {
		Fixed	temp = *this;
		++*this;
		return (temp);
	}

//MEMBERS FUNCTION
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
		return ((float)this->value / (1 << this->nbr_fract_bits));
	}
	//Return the value as an int
	int	Fixed::toInt( void ) const {
		return (this->value >> this->nbr_fract_bits);
	}
	//Return the min one
	Fixed&	Fixed::min(Fixed& var1, Fixed& var2) {
		if (var1 < var2)
			return (var1);
		return (var2);
	}
	//Return the min one
	Fixed&	Fixed::min(const Fixed& var1, const Fixed& var2) {
		if (var1.toFloat() < var2.toFloat())
		{
			Fixed& temp = (Fixed&)var1;
			return (temp);
		}
		Fixed& temp = (Fixed&)var2;
		return (temp);
	}
	//Return the max one
	Fixed&	Fixed::max(Fixed& var1, Fixed& var2) {
		if (var1 > var2)
			return (var1);
		return (var2);
	}
	//Return the max one
	Fixed&	Fixed::max(const Fixed& var1, const Fixed& var2) {

		if (var1.toFloat() > var2.toFloat())
		{
			Fixed& temp = (Fixed&)var1;
			return (temp);
		}
		Fixed& temp = (Fixed&)var2;
		return (temp);
	}


