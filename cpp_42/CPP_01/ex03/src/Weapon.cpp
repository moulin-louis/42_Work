/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 13:30:02 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/15 16:17:38 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

Weapon::Weapon( std::string type )
{
	this->type = type;
	std::cout << "Weapon constructor" << std::endl;
	return ;
}

Weapon::Weapon( void )
{
	return ;
}

Weapon::~Weapon( void )
{
	std::cout << "Weapon destructor" << std::endl;
	return ;
}

const std::string	Weapon::getType( void )
{
	return (this->type);
}

void	Weapon::setType( std::string type )
{
	this->type = type;
	return ;
}