/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 17:55:30 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/20 18:14:33 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

ScavTrap::ScavTrap( void )
{
	std::cout << "ScavTrap default contrusctor called" << std::endl;
	this->hit_point = 100;
	this->energy_point = 50;
	this->attack_dmg = 20;
	return ;
}

ScavTrap::ScavTrap( const std::string& input )
{
	std::cout << "ScavTrap constructor with name called" << std::endl;
	this->name = input;
	this->hit_point = 100;
	this->energy_point = 50;
	this->attack_dmg = 20;
	return ;
}

ScavTrap::ScavTrap( const ScavTrap& var)
{
	std::cout << "ScavTrap constructor by copy called" << std::endl;
	this->name = var.name;
	this->hit_point = var.hit_point;
	this->energy_point = var.energy_point;
	this->attack_dmg = var.attack_dmg;
	return ;
}

ScavTrap::~ScavTrap( void )
{
	std::cout << "ScavTrap default destructor called" << std::endl;
}

ScavTrap& ScavTrap::operator=( const ScavTrap& var)
{
	this->name = var.name;
	this->hit_point = var.hit_point;
	this->energy_point = var.energy_point;
	this->attack_dmg = var.attack_dmg;
	return (*this);
}

void	ScavTrap::attack(const std::string& target)
{
	if (this->energy_point > 0)
	{
		if (this->attack_dmg <= 0)
		{
			std::cout << this->name << " cant attack cause he would deal 0 dammage" << std::endl;
			return ;
		}
		std::cout << "ScavTrap " << this->name << " attacks " << target << ", dealing ";
		std::cout << this->attack_dmg << " damage!" << std::endl;
		return ;
	}
	std::cout << this->name << " have 0 energy." << std::endl;
	return ;
}

void	ScavTrap::guardGate( void )
{
	std::cout << "ScavTrap is now protecting the gate" << std::endl;
	return ;
}