/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 13:57:15 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/15 16:45:52 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanB.hpp"

HumanB::HumanB( std::string name , Weapon& weapon )
{
	std::cout << "HumanB constructor called" << std::endl;
	this->name = name;
	this->weapon = &weapon;
	return ;
}

HumanB::HumanB( std::string name )
{
	std::cout << "HumanB constructor called" << std::endl;
	this->name = name;
	this->weapon = NULL;
	return ;
}

HumanB::~HumanB( void )
{
	std::cout << "HumanB destructor called" << std::endl;
	return ;
}

void	HumanB::setWeapon( Weapon& weapon )
{
	this->weapon = &weapon;
	return ;
}

void	HumanB::attack( void )
{
	if (this->weapon == NULL)
	{
		std::cout << this->name << "dont have any weapon" << std::endl;
		return ;
	}
	std::cout << this->name << " attacks with their " << this->weapon->getType() << std::endl;
	return ;
}