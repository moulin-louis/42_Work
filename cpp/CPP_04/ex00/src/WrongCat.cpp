/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 13:28:21 by loumouli          #+#    #+#             */
/*   Updated: 2023/03/17 10:13:43 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongCat.hpp"

WrongCat::WrongCat( void ) {
	std::cout << "WrongCat default constructor called" << std::endl;
	this->type = "WrongCat";
	return ;
}

WrongCat::WrongCat( const WrongCat& var ) {
	std::cout << "WrongCat constructor by copy called" << std::endl;
	*this = var;
	return ;
}

WrongCat::~WrongCat( void ) {
	std::cout << "WrongCat default destructor called" << std::endl;
	return ;
}

void	WrongCat::makeSound( void ) const {
	std::cout << "miaou miaou" << std::endl;
	return ;
}

WrongCat&	WrongCat::operator=( const WrongCat& var ) {
	this->type = var.type;
	return (*this);
}

std::string& WrongCat::getType( void ) { return(this->type); }