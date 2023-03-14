/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:28:18 by loumouli          #+#    #+#             */
/*   Updated: 2023/03/14 15:33:59 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main( int ac, char **av ) {
	if (ac != 2 ) {
		std::cout << "Wrong nbr of args" << std::endl;
		return (1);
	}

	RPN foo;
	try {
		foo.process_input(av[1]);
	}
	catch (std::invalid_argument& x) {
		std::cout << "Error: " << x.what() << std::endl;
		return (1);
	}

}