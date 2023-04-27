/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 11:58:21 by loumouli          #+#    #+#             */
/*   Updated: 2023/03/17 10:30:05 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat( void ) {
	// std::cout << "Cat default constructor called" << std::endl;
	this->type = "Cat";
	this->my_brain = new Brain;
	return ;
}

Cat::Cat( const Cat& var ) {
	*this = var;
	return ;
}

Cat::~Cat( void ) {
	// std::cout << "Cat default destructor called" << std::endl;
	delete this->my_brain;
	return ;
}

void	Cat::makeSound( void ) const {
	std::cout << "miaou miaou" << std::endl;
}

std::string& Cat::getType( void ) { return(this->type); }

Brain*	Cat::get_brain( void ) const { return (this->my_brain); }

Cat&	Cat::operator=( const Cat& var ) {
	// std::cout << "Cat assignation called" << std::endl;
	this->type = var.type;
	*(this->my_brain) = *(var.my_brain);
	return (*this);
}

void Cat::display_brain( void ) {
	this->my_brain->display_brain();
	return ;
}

void Cat::set_idea( int idx, std::string const& id ) {
	this->my_brain->set_idea(idx, id);
	return;
}
