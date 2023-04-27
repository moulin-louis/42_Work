/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:15:33 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/20 18:11:30 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

int	main( void )
{
	std::cout << "Creation ClapTrap instance..." << std::endl;
	ClapTrap perso1("Perso1");

	std::cout << std::endl << "Creation ScavTrap instance..." << std::endl;
	ScavTrap perso2("Perso2");

	std::cout << std::endl;
	perso1.attack("Perso2");
	perso2.takeDamage(perso1.get_dmg());

	std::cout << std::endl;
	perso2.attack("Perso1");
	perso1.takeDamage(perso2.get_dmg());
	perso2.guardGate();
	std::cout << std::endl << "Calling destructor..." << std::endl;

}