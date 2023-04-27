/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 17:44:25 by loumouli          #+#    #+#             */
/*   Updated: 2023/03/16 18:05:05 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MateriaSource.hpp"

MateriaSource::MateriaSource( void ) {
	this->len_source = 0;
	this->source = new AMateria*[1];
	this->source[0] = NULL;
	return ;
}

MateriaSource::MateriaSource( const MateriaSource& var ) {
	*this = var;
	return ;
}

MateriaSource& MateriaSource::operator=( const MateriaSource& var ) {
	this->len_source = var.len_source;
	this->source = new AMateria*[this->len_source];
	for (int i = 0; var.source[i]; i++)
	{
		if (this->source[i])
			delete this->source[i];
		this->source[i] = var.source[i]->clone();
	}
	return *this;
}

MateriaSource::~MateriaSource( void ) {
	for (int i = 0; this->source[i]; i++) {
		delete this->source[i];
	}
	delete[] this->source;
}

void MateriaSource::learnMateria( AMateria* material ) {
	if (this->source[0] == NULL ) {
		delete[] this->source;
		this->source = new AMateria*[2];
		this->source[0] = material;
		this->source[1] = NULL;
		return ;
	}
	int len = -1;
	while (this->source[++len])
		;
	len +=1;
	AMateria **temp = new AMateria*[len + 1];
	for (int i = 0; this->source[i]; i++) {
		temp[i] = this->source[i];
	}
	temp[len - 1] = material;
	temp[len] = NULL;
	delete[] this->source;
	this->source = temp;
}

AMateria* MateriaSource::createMateria( std::string const& type_i ) {
	for (int i = 0; this->source[i]; i++) {
		if (this->source[i]->getType() == type_i) {
			return this->source[i]->clone();
		}
	}
	return NULL;
}