/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 13:43:46 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/23 15:18:02 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"


Dog::Dog( void )
{
	std::cout << "Dog default constructor" << std::endl;
	this->type = "Dog";
	this->my_brain = new Brain;
	return ;
}

Dog::~Dog( void )
{
	std::cout << "Dog destructor called" << std::endl;
	if (this->my_brain)
		delete this->my_brain;
	this->my_brain = NULL;
	return ;
}

void	Dog::makeSound( void ) const
{
	std::cout << "wouaf wouaf" << std::endl;
}

std::string& Dog::getType( void ) { return(this->type); }

Brain*	Dog::get_brain( void ) const { return (this->my_brain); }

Dog& Dog::operator=( const Dog& var )
{
	std::cout << "Dog constructor by assignation called" << std::endl;
	for (int i = 0; i < 100; i++)
	{
		this->my_brain->ideas[i] = var.my_brain->ideas[i];
	}
	this->type = var.type;
	return (*this);
}