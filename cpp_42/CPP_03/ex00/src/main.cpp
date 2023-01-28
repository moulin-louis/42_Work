/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:15:33 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/20 15:19:29 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

int	main( void )
{
	{ClapTrap	perso1("Perso1");
	ClapTrap	perso2("Perso2");

	perso1.attack("Perso2");
	perso2.takeDamage(perso1.get_dmg());
	perso1.setDamage(2);
	perso1.attack("Perso2");
	perso2.takeDamage(perso1.get_dmg());}

	{ClapTrap	perso1("Perso1");
	ClapTrap perso3(perso1);
	perso3.attack("test");
	std::cout << std::endl;}

	{
	ClapTrap perso4;
	ClapTrap perso5("perso5");
	perso4 = perso5;
	perso4.attack("test5");}
}