/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 11:53:00 by loumouli          #+#    #+#             */
/*   Updated: 2023/03/17 10:16:26 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef DOG_H
#define DOG_H

#include "Animal.hpp"

class Dog : public Animal {
	public:
		Dog( void );
		Dog( const Dog& );
		~Dog( void );
		void	makeSound( void ) const ;
		std::string& getType( void );
		Dog&	operator=(const Dog& );
};

#endif