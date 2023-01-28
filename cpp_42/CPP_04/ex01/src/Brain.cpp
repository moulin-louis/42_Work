/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 13:48:28 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/23 13:53:55 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Brain.hpp"

Brain::Brain( void )
{
	std::cout << "Brain default constructor called" << std::endl;
	return ;
}

Brain::Brain( const Brain& var)
{
	std::cout << "Brain contructor by copy called" << std::endl;
	for (int i = 0; i < 100; i++) {
		this->ideas[i] = var.ideas[i];
	}
	return ;
}

Brain::~Brain( void )
{
	std::cout << "Brain default destructor called" << std::endl;
	return ;
}

Brain& Brain::operator=(const Brain& var)
{
	std::cout << "Brain contructor by assignation called" << std::endl;
	for (int i = 0; i < 100; i++) {
		this->ideas[i] = var.ideas[i];
	}
	return (*this);
}