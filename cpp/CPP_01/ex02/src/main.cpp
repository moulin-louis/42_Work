/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 13:15:10 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/15 13:23:46 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

int	main( void )
{
	std::string		var = "HI THIS IS BRAIN";
	std::string*	stringPTR = &var;
	std::string&	stringREF = var;

	std::cout << "address of string is =  " << &var << std::endl;
	std::cout << "stringPTR addres held = " << stringPTR << std::endl;
	std::cout << "stringREF addres held = " << &stringREF << std::endl;
	std::cout << std::endl;
	std::cout << "value of string is           " << var << std::endl;
	std::cout << "value pointed by stringPTR = " << *stringPTR << std::endl;
	std::cout << "value pointed by stringREF = " << stringREF << std::endl;
	return (0);
}