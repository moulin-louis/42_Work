/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:28:56 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/27 17:31:36 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Data.hpp"

Data::Data( void )
{
	std::cout << "Data default constructor called" << std::endl;
	this->value = 42;
	return ;
}

Data::Data( const Data& var )
{
	std::cout << "Data constructor by copy called" << std::endl;
	this->value = var.value;
	return ;
}

Data::~Data( void )
{
	std::cout << "Data default destructor called" << std::endl;
	return ;
}

Data& Data::operator=( const Data& var )
{
	std::cout << "Data constructor by copy called" << std::endl;
	this->value = var.value;
	return (*this);
}