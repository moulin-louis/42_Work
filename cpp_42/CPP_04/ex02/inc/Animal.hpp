/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 11:38:27 by loumouli          #+#    #+#             */
/*   Updated: 2023/03/17 10:16:51 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef ANIMAL_H
#define ANIMAL_H

#include <iostream>
#include "Brain.hpp"

class	Animal {
	protected:
		std::string type;
	public:
		Animal( void );
		Animal( const Animal& );
		virtual ~Animal( void );
		virtual void makeSound( void ) const;
		std::string getType( void )  const;
		virtual Brain* get_brain( void ) const = 0;
		virtual Animal& operator=(const Animal& );
};

#endif