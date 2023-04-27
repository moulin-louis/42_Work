/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 11:53:00 by loumouli          #+#    #+#             */
/*   Updated: 2023/03/17 10:28:17 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef DOG_H
#define DOG_H

#include <iostream>
#include "Animal.hpp"
#include "Brain.hpp"

class Dog : public Animal {
	private:
		Brain*	my_brain;
	public:
		Dog( void );
		Dog( const Dog& );
		~Dog( void );
		void	makeSound( void ) const ;
		std::string& getType( void );
		virtual	Brain*	get_brain( void ) const;
		Dog&	operator=(const Dog& var);
		void display_brain( void );
		void set_idea( int, std::string const& );
};

#endif