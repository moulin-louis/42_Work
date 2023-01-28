/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:45:42 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/27 18:02:06 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"
#include <iostream>

int main( void ) {
	int a = 2;
	int b = 3;
	std::cout << "a = " << a << ", b = " << b << std::endl;
	std::cout << "on swap" << std::endl;
	::swap( a, b );
	std::cout << "a = " << a << ", b = " << b << std::endl;
	std::cout << "min( a, b ) = " << ::min( a, b ) << std::endl;
	std::cout << "max( a, b ) = " << ::max( a, b ) << std::endl;
	std::string c = "chaine1";
	std::string d = "chaine2";
	std::cout << "c = " << c << ", d = " << d << std::endl;
	std::cout << "on swap" << std::endl;
	::swap(c, d);
	std::cout << "c = " << c << ", d = " << d << std::endl;
	std::cout << "min( c, d ) = " << ::min( c, d ) << std::endl;
	std::cout << "max( c, d ) = " << ::max( c, d ) << std::endl;
	return 0;
}