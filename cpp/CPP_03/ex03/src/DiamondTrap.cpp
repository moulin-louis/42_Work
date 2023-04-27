/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 18:56:18 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/20 19:49:22 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap( void )
{
	std::cout << "DiamondTrap default constructor called" << std::endl;
	this->hit_point = FragTrap::hit_point;
	this->energy_point = ScavTrap::energy_point;
	this->attack_dmg = FragTrap::attack_dmg;;
	return ;
}

DiamondTrap::DiamondTrap( const std::string& input )
{
	std::cout << "DiamondTrap constructor with name called" << std::endl;
	ClapTrap::name = input;
	ClapTrap::name += "_clap_name";
	this->name = input;
	this->hit_point = FragTrap::hit_point;
	this->energy_point = ScavTrap::energy_point;
	this->attack_dmg = 30;
	return ;
}

DiamondTrap::DiamondTrap( const DiamondTrap& var )
{
	std::cout << "DiamondTrap constructor by copy called" << std::endl;
	*this = var;
	return ;
}

DiamondTrap::~DiamondTrap( void )
{
	std::cout << "DiamondTrap default destructor" << std::endl;
	return ;
}

void	DiamondTrap::whoAmI( void )
{
	std::cout << "My name is " << this->name << " and my clap name is " << this->ClapTrap::name << std::endl;
}

int	DiamondTrap::get_dmg( void ) { return (this->attack_dmg); }
int	DiamondTrap::get_energy( void ) { return (this->energy_point); }
int	DiamondTrap::get_hit( void ) { return (this->hit_point); }

DiamondTrap& DiamondTrap::operator=(const DiamondTrap& var)
{
	std::cout << "DiamondTrap constructor by assignation called" << std::endl;
	this->name = var.name;
	this->hit_point = var.hit_point;
	this->energy_point = var.energy_point;
	this->attack_dmg = var.attack_dmg;
	this->ClapTrap::name = var.ClapTrap::name;
	return (*this);
}
