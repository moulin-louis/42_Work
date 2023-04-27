/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:23:41 by loumouli          #+#    #+#             */
/*   Updated: 2023/03/16 18:04:38 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Character.hpp"

Character::Character( void ) {
	this->len_inventory = 0;
	this->trash = NULL;
	for (int i = 0; i < 4; i++) {
		this->inventory[i] = NULL;
	}
	return ;
}

Character::Character( std::string name_i ) {
	this->len_inventory = 0;
	this->trash = NULL;
	this->name = name_i;
	for (int i = 0; i < 4; i++) {
		this->inventory[i] = NULL;
	}
	return ;
}

Character::Character( const Character& var ) {
	*this = var;
	return ;
}

Character::~Character( void ) {
	for (int i = this->len_inventory -1; i != -1; i--) {
		if (this->inventory[i])
			delete this->inventory[i];
	}
	if (this->trash) {
		for (int i = 0; this->trash[i]; i++)
			delete this->trash[i];
		delete[] this->trash;
	}
	return ;
}

Character& Character::operator=( const Character& var ) {
	for ( int i = 0; i < 4; i++) {
		if (this->inventory[i])
			delete this->inventory[i];
		this->inventory[i] = var.inventory[i]->clone();
	}
	this->name = var.name;
	this->len_inventory = var.len_inventory;
	return *this;
}

std::string const& Character::getName( void ) const {
	return this->name;
}

void Character::add_to_trash( AMateria* material ) {
	if (this->trash == NULL) {
		this->trash = new AMateria*[2];
		this->trash[0] = material;
		this->trash[1] = NULL;
		return ;
	}
	int len = -1;
	while (this->trash[++len])
		;
	AMateria **temp = new AMateria*[len + 1];
	for (int i = 0; this->trash[i]; i++) {
		temp[i] = this->trash[i];
	}
	temp[len - 1] = material;
	temp[len] = NULL;
	delete[] this->trash;
	this->trash = temp;
}

void Character::equip( AMateria* material ) {
	if (!material) {
		return ;
	}
	if (this->len_inventory == 4) {
		return ;
	}
	this->inventory[this->len_inventory] = material;
	this->len_inventory++;
}

void Character::unequip( int idx ) {
	if (idx < 0 || idx >= this->len_inventory ) {
		return ;
	}
	this->add_to_trash(this->inventory[idx]);
	this->inventory[idx] = NULL;
	for (int i = idx; i < (this->len_inventory - 1); i++) {
		this->inventory[i] = this->inventory[i + 1];
	}
	this->len_inventory--;
}

void Character::use( int idx, ICharacter& target ) {
	if (idx < 0 || idx >= this->len_inventory) {
		return ;
	}
	this->inventory[idx]->use(target);
}

void Character::display_inventory( void ) {
	std::cout << "Inventory : " << std::endl;
	for (int i = 0; i != this->len_inventory; i++) {
		std::cout << i << ": " << this->inventory[i]->getType() << std::endl;
	}
}

void Character::display_trash( void ) {
	std::cout << "Trash : "  << std::endl;
	for (int i = 0; this->trash[i]; i++) {
		std::cout << i << ": " << this->trash[i]->getType() << std::endl;
	}
}