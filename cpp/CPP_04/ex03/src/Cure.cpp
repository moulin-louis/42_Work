/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:09:51 by loumouli          #+#    #+#             */
/*   Updated: 2023/03/16 16:16:02 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cure.hpp"

Cure::Cure( void ) {
	this->type = "cure";
	return ;
}

Cure* Cure::clone( void ) const {
	Cure* result = new Cure;
	result->type = this->type;
	return result;
}

void Cure::use( ICharacter& charac ) {
	std::cout << "* heals " << charac.getName() << "'s wounds" << std::endl;
	return ;
}