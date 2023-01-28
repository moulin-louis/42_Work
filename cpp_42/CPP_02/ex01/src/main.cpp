/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 17:22:30 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/17 12:19:41 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include <bits/stdc++.h>

int main( void )
{
	//Creating all variable
	Fixed a;
	Fixed const b( 10 );
	Fixed const c( 42.42f );
	Fixed const d( b );
	a = Fixed( 1234.4321f );

	//Testing << overload, should display a float
	std::cout << "a is " << a << std::endl;
	std::cout << "should be 1234.43" << std::endl;
	std::cout << std::endl;

	std::cout << "b is " << b << std::endl;
	std::cout << "should be 10" << std::endl;
	std::cout << std::endl;

	std::cout << "c is " << c << std::endl;
	std::cout << "should be 42.4219" << std::endl;
	std::cout << std::endl;

	std::cout << "d is " << d << std::endl;
	std::cout << "should be 10" << std::endl;
	std::cout << std::endl;


	//Testint toInt() fn, should display the same number thaht upsido but as an int
	std::cout << "a is " << a.toInt() << " as integer" << std::endl;
	std::cout << "should be 1234" << std::endl;
	std::cout << std::endl;

	std::cout << "b is " << b.toInt() << " as integer" << std::endl;
	std::cout << "should be 10" << std::endl;
	std::cout << std::endl;

	std::cout << "c is " << c.toInt() << " as integer" << std::endl;
	std::cout << "should be 42" << std::endl;
	std::cout << std::endl;

	std::cout << "d is " << d.toInt() << " as integer" << std::endl;
	std::cout << "should be 10" << std::endl;
	std::cout << std::endl;

	return 0;
}