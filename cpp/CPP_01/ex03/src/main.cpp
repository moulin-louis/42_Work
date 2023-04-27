/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 14:02:58 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/15 16:49:21 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanA.hpp"
#include "HumanB.hpp"

int main( void )
{
	{
		std::cout << "Creating HumanA..." << std::endl;
		Weapon club = Weapon("crude spiked club");
		HumanA bob("Bob", club);
		bob.attack();
		std::cout << "Changing the weapon..." << std::endl;
		club.setType("some other type of club");
		bob.attack();
		std::cout << "Destroying HumanA..." << std::endl;
	}
	std::cout << std::endl;
	{
		std::cout << "Creating HumanB..." << std::endl;
		Weapon club = Weapon("crude spiked club");
		HumanB jim("Jim");
		jim.setWeapon(club);
		jim.attack();
		std::cout << "Changing the weapon..." << std::endl;
		club.setType("some other type of club");
		jim.attack();
		std::cout << "Destroying HumanB..." << std::endl;
	}
	return 0;
}