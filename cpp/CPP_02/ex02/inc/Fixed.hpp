/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:00:04 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/20 13:43:56 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <cmath>

class Fixed
{
private:
	//PRIVATE VAR
		int		value;
		static	const	int	nbr_fract_bits = 8;
	//PRIVATE MEMBER FUNCTION
		//Overload stream operator
		friend 	std::ostream & operator<<(std::ostream& os, const Fixed& var);
public:
	//CONSTRUCTOR/DESTRUCTOR
		//Default constructor
		Fixed	( void );
		//Constrcutor with an int
		Fixed	( const int i);
		//Constructor with an float
		Fixed	( const double i);
		//Constructor with a Fixed instance as arg
		Fixed	( const Fixed&);
		//Default destructor
		~Fixed	();
	//PUBLIC MEMBERS FUNCTION
		int		getRawBits( void );
		void	setRawBits( int const raw );
		float	toFloat( void ) const;
		int		toInt( void ) const;
		static	Fixed&	min(Fixed& var1, Fixed& var2);
		static	Fixed&	min(const Fixed& var1, const Fixed& var2);
		static	Fixed&	max(Fixed& var1, Fixed& var2);
		static	Fixed&	max(const Fixed& var1, const Fixed& var2);

	//OVERlOAD OPERATOR
		//Overload asignation operator
		Fixed&	operator=(const Fixed *var);
		//Overload comparaisons operator
		bool	operator<(const Fixed& var);
		bool	operator>(const Fixed& var1);
		bool	operator<=(const Fixed& var1);
		bool	operator>=(const Fixed& var1);
		bool	operator==(const Fixed& var1);
		bool	operator!=(const Fixed& var1);
		//Overload arithmetic operators
		Fixed&	operator+(const Fixed& var);
		Fixed&	operator-(const Fixed& var);
		Fixed&	operator*(const Fixed& var);
		Fixed& 	operator/(const Fixed& var);
		//Overload incre/decremnt operators
		Fixed&	operator++( void );
		Fixed	operator++(int);
		Fixed&	operator--( void );
		Fixed	operator--(int);
		
};

