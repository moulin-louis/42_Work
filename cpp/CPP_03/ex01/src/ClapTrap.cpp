/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:52:28 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/20 15:27:56 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

ClapTrap::ClapTrap( void )
{
	std::cout << "ClapTrap default constructor called" << std::endl;
	return ;
}

ClapTrap::ClapTrap( std::string name )
{
	std::cout << "ClapTrap string constructor called" << std::endl;
	this->name = name;
	this->hit_point = 10;
	this->energy_point = 10;
	this->attack_dmg = 0;
	return ;
}

ClapTrap::ClapTrap( const ClapTrap& var )
{
	std::cout << "ClapTrap constructor by copy called" << std::endl;
	this->name = var.name;
	this->hit_point = var.hit_point;
	this->energy_point = var.energy_point;
	this->attack_dmg = var.attack_dmg;
	return ;
}

ClapTrap::~ClapTrap( void )
{
	std::cout << "ClapTrap default destructor called" << std::endl;
	return ;
}

int	ClapTrap::get_dmg( void ) { return (this->attack_dmg); }

void	ClapTrap::attack( const std::string& target)
{
	if (this->energy_point > 0)
	{
		if (this->attack_dmg <= 0)
		{
			std::cout << this->name << " cant attack cause he would deal 0 dammage" << std::endl;
			return ;
		}
		std::cout << "ClapTrap " << this->name << " attacks " << target << ", dealing ";
		std::cout << this->attack_dmg << " damage!" << std::endl;
		return ;
	}
	std::cout << this->name << " have 0 energy." << std::endl;
	return ;
}

void	ClapTrap::takeDamage(unsigned int amount)
{
	if (amount <= 0)
	{
		std::cout << this->name << " cant take damage if you attack with 0 AD" << std::endl;
		return ;
	}
	std::cout << this->name << " take " << amount << " damage" << std::endl;
	return ;
}

void	ClapTrap::beRepaired( unsigned int amount)
{
	if (this->energy_point > 0)
	{
		std::cout << "ClapTrap " << this->name << "has been heal for " << amount << " HP!" << std::endl;
		this->energy_point += amount;
	}
	std::cout << this->name << " have 0 energy." << std::endl;
	return ;
}

void	ClapTrap::setDamage( int amount )
{
	std::cout << this->name << " damage has been set to " << amount << std::endl;
	this->attack_dmg = amount;
}

ClapTrap&	ClapTrap::operator=(const ClapTrap& var)
{
	std::cout << "ClapTrap constructor by assignation called" << std::endl;
	this->name = var.name;
	this->hit_point = var.hit_point;
	this->energy_point = var.energy_point;
	this->attack_dmg = var.attack_dmg;
	return (*this);
}
