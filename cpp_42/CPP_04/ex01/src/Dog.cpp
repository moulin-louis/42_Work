/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 13:43:46 by loumouli          #+#    #+#             */
/*   Updated: 2023/03/17 10:29:11 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"


Dog::Dog( void ) {
	// std::cout << "Dog default constructor" << std::endl;
	this->type = "Dog";
	this->my_brain = new Brain;
	return ;
}

Dog::~Dog( void ) {
	// std::cout << "Dog destructor called" << std::endl;
	delete this->my_brain;
	return ;
}

void	Dog::makeSound( void ) const {
	std::cout << "wouaf wouaf" << std::endl;
	return ;
}

std::string& Dog::getType( void ) { return(this->type); }

Brain*	Dog::get_brain( void ) const { return (this->my_brain); }

Dog& Dog::operator=( const Dog& var ) {
	// std::cout << "Dog constructor by assignation called" << std::endl;
	*(this->my_brain) = *(var.my_brain);
	this->type = var.type;
	return (*this);
}

void Dog::display_brain( void ) {
	this->my_brain->display_brain();
	return ;
}

void Dog::set_idea( int idx, std::string const& id ) {
	this->my_brain->set_idea(idx, id);
	return;
}