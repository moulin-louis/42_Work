/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 19:26:50 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/15 12:42:50 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"


Zombie::Zombie (std::string name)
{
	this->name = name;
	return ;
}

Zombie::Zombie ( void )
{
	std::cout << "Zombie constructor" << std::endl;
	return ;
}

Zombie::~Zombie (void)
{
	std::cout << this->name << " destroyed" << std::endl;
	return ;
}

void	Zombie::announce( void )
{
	std::cout << name << ": BraiiiiiiinnnzzzZ..." << std::endl;
	return ;
}

void	Zombie::name_it( std::string name )
{
	this->name = name;
	return ;
}