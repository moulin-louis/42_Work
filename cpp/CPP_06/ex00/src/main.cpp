/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 13:16:01 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/27 16:38:05 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Conversion.hpp"

void	displaychar( const std::string& input )
{
	if( input.size() == 1 && isdigit(input[0]) == false)
		std::cout << "char: " << static_cast<char>(input[0]) << std::endl;
	else
	{
		std::cout << "char: ";
		int result = 0;
		atoi_char(&result, input);
		if (result < 0 || result > 127)
		{
			std::cout << "impossibe" << std::endl;
			return ;
		}
		else if (!std::isprint(result))
		{
			std::cout << "non printable" << std::endl;
			return ;
		}
		std::cout << "" << static_cast<char>(result) << std::endl;
	}
}

void	displayint( const std::string& input )
{
	int	result = 0;
	std::cout << "int: ";
	atoi_int(&result, input);
	std::cout << static_cast<int>(result) << std::endl;
}

void	displayfloat( const std::string& input )
{
	float result = std::strtof(input.c_str(), NULL);
	if (errno == ERANGE)
	{
		std::cout << "float: overflow" << std::endl;
		return;
	}
	if (result == HUGE_VALF)
	{
		std::cout << "float: inff" << std::endl;
		return ;
	}
	if (result == -HUGE_VALF)
	{
		std::cout << "float: -inff" << std::endl;
		return ;
	}
	std::cout << "float: " << static_cast<float>(result);
	if (roundf(result) == result)
		std::cout << ".0";
	std::cout << "f" << std::endl;
}

void	displaydouble( const std::string& input )
{
	double result = std::strtod(input.c_str(), NULL);
	if (errno == ERANGE)
	{
		std::cout << "float: overflow" << std::endl;
		return;
	}
	if (result == HUGE_VAL)
	{
		std::cout << "float: inf" << std::endl;
		return ;
	}
	if (result == -HUGE_VAL)
	{
		std::cout << "float: -inf" << std::endl;
		return ;
	}
	std::cout << "double: " << static_cast<double>(result);
	if (roundf(result) == result)
		std::cout << ".0";
	std::cout << std::endl;
}

int	main( int ac, char **av )
{
	if (ac != 2)
	{
		std::cout << "Gib valid nbr of args" << std::endl;
		return (1);
	}
	std::string input = av[1];
	try {
		displaychar(input);
	}
	catch (std::invalid_argument& mce) {
		std::cout << mce.what() << std::endl;
	}
	catch (std::out_of_range& mce) {
		std::cout << mce.what() << std::endl;
	}
	try {
		displayint(input);
	}
	catch (std::invalid_argument& mce) {
		std::cout << mce.what() << std::endl;
	}
	catch (std::out_of_range& mce) {
		std::cout << mce.what() << std::endl;
	}
	try {
		displayfloat(input);
	}
	catch (std::invalid_argument& mce) {
		std::cout << mce.what() << std::endl;
	}
	catch (std::out_of_range& mce) {
		std::cout << mce.what() << std::endl;
	}
	try {
		displaydouble(input);
	}
	catch (std::invalid_argument& mce) {
		std::cout << mce.what() << std::endl;
	}
	catch (std::out_of_range& mce) {
		std::cout << mce.what() << std::endl;
	}
}