/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 13:53:29 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/15 16:20:29 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanA.hpp"

HumanA::HumanA( std::string name, Weapon& weapon )
{
	std::cout << "HumanA constructor called" << std::endl;
	this->name = name;
	this->weapon = &weapon; 
	return ;
}

HumanA::~HumanA( void )
{
	std::cout << "HumanA destructor called" << std::endl;
	return ;
}

void	HumanA::attack( void )
{
	std::cout << this->name << " attacks with their " << this->weapon->getType() << std::endl;
	return ;
}