/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 13:29:35 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/23 13:30:16 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal( void )
{
	std::cout << "WrongAnimal default constructor called" << std::endl;
	this->type = "WrongAnimal";
	return ;
}

WrongAnimal::WrongAnimal( const WrongAnimal& var)
{
	this->type = var.type;
	std::cout  << "WrongAnimal contructor by copy called" << std::endl;
	return ;
}

WrongAnimal::~WrongAnimal( void )
{
	std::cout << "WrongAnimal default destructor called" << std::endl;
	return ;
}

void	WrongAnimal::makeSound( void ) const
{
	std::cout << "Default WrongAnimal sound...." << std::endl;
	return ;
}

std::string WrongAnimal::getType( void ) const { return(this->type); }

WrongAnimal&	WrongAnimal::operator=( const WrongAnimal& var )
{
	this->type = var.type;
	std::cout << "WrongAnimal constructror by assignation called" << std::endl;
	return (*this);
}