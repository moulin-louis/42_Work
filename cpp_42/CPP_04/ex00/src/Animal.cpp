/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 11:54:14 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/23 13:21:04 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"

Animal::Animal( void )
{
	std::cout << "Animal default constructor called" << std::endl;
	this->type = "Animal";
	return ;
}

Animal::Animal( const Animal& var)
{
	this->type = var.type;
	std::cout  << "Animal contructor by copy called" << std::endl;
	return ;
}

Animal::~Animal( void )
{
	std::cout << "Animal default destructor called" << std::endl;
	return ;
}

void	Animal::makeSound( void ) const
{
	std::cout << "Default animal sound...." << std::endl;
	return ;
}

std::string Animal::getType( void ) const { return(this->type); }

Animal&	Animal::operator=( const Animal& var )
{
	this->type = var.type;
	std::cout << "Animal constructror by assignation called" << std::endl;
	return (*this);
}