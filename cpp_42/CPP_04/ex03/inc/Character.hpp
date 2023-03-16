/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:19:28 by loumouli          #+#    #+#             */
/*   Updated: 2023/03/16 17:28:10 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "ICharacter.hpp"
#include "AMateria.hpp"
#include "ICharacter.hpp"

class ICharacter;

class Character : public ICharacter {
	private:
		AMateria*	inventory[4];
		std::string name;
		int			len_inventory;
		AMateria	**trash;
	public:
		Character( void );
		Character( std::string );
		Character( const Character& );
		~Character( void );
		Character& operator=( const Character& );
		void	add_to_trash( AMateria* );
		virtual std::string const & getName() const;
		virtual void equip(AMateria*);
		virtual void unequip(int);
		virtual void use(int, ICharacter&);
		void	display_inventory( void );
		void	display_trash( void );
};

#endif