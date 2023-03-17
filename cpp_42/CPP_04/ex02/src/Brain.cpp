/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 13:48:28 by loumouli          #+#    #+#             */
/*   Updated: 2023/03/17 10:32:41 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Brain.hpp"

Brain::Brain( void ) {
	// std::cout << "Brain default constructor called" << std::endl;
	return ;
}

Brain::Brain( const Brain& var) {
	// std::cout << "Brain contructor by copy called" << std::endl;
	*this = var;
	return ;
}

Brain::~Brain( void ) {
	// std::cout << "Brain default destructor called" << std::endl;
	return ;
}

Brain& Brain::operator=(const Brain& var) {
	// std::cout << "Brain assignation called" << std::endl;
	for (int i = 0; !var.ideas[i].empty(); i++) {
		this->ideas[i] = var.ideas[i];
	}
	return (*this);
}

void Brain::display_brain( void ) {
	for (int i = 0; !this->ideas[i].empty(); i++) {
		std::cout << "ideas[" << i << "] = " << this->ideas[i] << std::endl;
	}
}

void Brain::set_idea( int idx, std::string const& id ) {
	if (idx < 0 || idx >= 100 ) {
		return ;
	}
	this->ideas[idx] = id;
}