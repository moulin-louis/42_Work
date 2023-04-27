/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:15:33 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/20 19:42:09 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"
#include "DiamondTrap.hpp"

int	main( void )
{
	std::cout << "Creating DiamondTrap instance..." << std::endl;
	DiamondTrap perso1("Perso1");
	std::cout << std::endl;
	std::cout << "Testing DiamondTrap attributs..." << std::endl;
	ClapTrap	perso2("Perso2");
	std::cout << std::endl;
	perso1.attack("TEST");
	perso2.takeDamage(perso1.get_dmg());
	perso1.whoAmI();
	std::cout << "DiamondTrap current stat" << std::endl;
	std::cout << "Attack:" << perso1.get_dmg() << std::endl;
	std::cout << "Energy:" << perso1.get_energy() << std::endl;
	std::cout << "Hit:" << perso1.get_hit() << std::endl;
	std::cout << "DiamondTrap stat should be :" << std::endl;
	std::cout << "Attack:30" << std::endl;
	std::cout << "Energy:50" << std::endl;
	std::cout << "Hit:100" << std::endl;
	std::cout << std::endl << "Calling destructor..." << std::endl;
}