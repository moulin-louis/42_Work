/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 13:43:46 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/23 13:20:52 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog( void )
{
	std::cout << "Dog default constructor" << std::endl;
	this->type = "Dog";
	return ;
}

Dog::Dog( const Dog& var )
{
	std::cout << "Dog constructor by copy called" << std::endl;
	this->type = var.type;
	return ;
}

Dog::~Dog( void )
{
	std::cout << "Dog destructor called" << std::endl;
	return ;
}

void	Dog::makeSound( void ) const
{
	std::cout << "wouaf wouaf" << std::endl;
}

std::string& Dog::getType( void ) { return(this->type); }

Dog& Dog::operator=( const Dog& var )
{
	std::cout << "Dog constructor by assignation called" << std::endl;
	this->type = var.type;
	return (*this);
}