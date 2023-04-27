/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 17:22:30 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/20 13:35:20 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"
#include <cmath>


unsigned long hashFunction(std::string key) {
    unsigned long hashCode = 0;
    for (int i = 0; i < (int)key.length(); i++) {
        hashCode += key[i] * pow(31, i);
    }
    return hashCode;
}
const	unsigned long debug_hash = 68167859;
const	unsigned long info_hash = 2423250;
const	unsigned long warning_hash = 65315656764;
const	unsigned long error_hash = 78163624;

int	main( int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "Wrong nbr of args" << std::endl;
		std::cout << "./harlFilter <minimun_level_info>" << std::endl;
		return (1);
	}
	std::string input = av[1];
	if (input.compare("DEBUG") != 0 && input.compare("INFO") != 0
		&& input.compare("WARNING") != 0 && input.compare("ERROR") != 0)
	{
		std::cout << "Wrong level of debug" << std::endl;
		std::cout << "Can be : DEBUG, INFO, WARNING, ERROR" << std::endl;
		return (1);
	}

	Harl	temp;
	switch (hashFunction(av[1]))
	{
		case debug_hash:
			std::cout << "Displaying debug message..." << std::endl;
			temp.complain("DEBUG");
			std::cout << std::endl;
		case info_hash:
			std::cout << "Displaying info message..." << std::endl;
			temp.complain("INFO");
			std::cout << std::endl;
		case warning_hash:
			std::cout << "Displaying warning message..." << std::endl;
			temp.complain("WARNING");
			std::cout << std::endl;
		case error_hash:
			std::cout << "Displaying error message..." << std::endl;
			temp.complain("ERROR");
			std::cout << std::endl;
	}
	return (0);
}