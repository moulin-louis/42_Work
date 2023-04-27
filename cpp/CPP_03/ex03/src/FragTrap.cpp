/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 18:38:00 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/20 18:48:59 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

FragTrap::FragTrap( void )
{
	std::cout << "FragTrap default constructor called" << std::endl;
	this->hit_point = 100;
	this->energy_point = 100;
	this->attack_dmg = 30;
	return ;
}

FragTrap::FragTrap( const std::string& input)
{
	std::cout << "FragTrap constructor with name called" << std::endl;
	this->name = input;
	this->hit_point = 100;
	this->energy_point = 100;
	this->attack_dmg = 30;
	return ;
}

FragTrap::FragTrap( const FragTrap& var)
{
	std::cout << "FragTrap constructor by copy called" << std::endl;
	this->name = var.name;
	this->hit_point = var.hit_point;
	this->energy_point = var.energy_point;
	this->attack_dmg = var.attack_dmg;
	return ;
}

FragTrap::~FragTrap( void )
{
	std::cout << "FragTrap default destructor" << std::endl;
}

FragTrap&	FragTrap::operator=(const FragTrap& var)
{
	std::cout << "FragTrap constructor by assignation called" << std::endl;
	this->name = var.name;
	this->hit_point = var.hit_point;
	this->energy_point = var.energy_point;
	this->attack_dmg = var.attack_dmg;
	return (*this);
}

void	FragTrap::highFivesGuys( void )
{
	std::cout << "FragTrap " << this->name << "succedfuly hit an High Five!" << std::endl;
	return ;
}