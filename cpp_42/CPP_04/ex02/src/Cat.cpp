/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 11:58:21 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/23 15:00:00 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat( void )
{
	std::cout << "Cat default constructor called" << std::endl;
	this->type = "Cat";
	this->my_brain = new Brain;
	this->my_brain->ideas[0] = "PLACEHOLDER";
	return ;
}

Cat::~Cat( void )
{
	std::cout << "Cat default destructor called" << std::endl;
	delete this->my_brain;
	return ;
}

void	Cat::makeSound( void ) const
{
	std::cout << "miaou miaou" << std::endl;
}

std::string& Cat::getType( void ) { return(this->type); }

Brain*	Cat::get_brain( void ) const { return (this->my_brain); }

Cat&	Cat::operator=( const Cat& var )
{
	this->type = var.type;
	for (int i = 0; i < 100; i++)
	{
		this->my_brain->ideas[i] = var.my_brain->ideas[i];
	}
	std::cout << "Cat assignation called" << std::endl;
	return (*this);
}
