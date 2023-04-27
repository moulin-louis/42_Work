/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 17:22:30 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/15 17:54:36 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

int	main( void )
{
	Harl	temp;

	std::cout << "Displaying debug message..." << std::endl;
	temp.complain("DEBUG");
	std::cout << std::endl;
	std::cout << "Displaying info message..." << std::endl;
	temp.complain("INFO");
	std::cout << std::endl;
	std::cout << "Displaying warning message..." << std::endl;
	temp.complain("WARNING");
	std::cout << std::endl;
	std::cout << "Displaying error message..." << std::endl;
	temp.complain("ERROR");
	return (0);
}