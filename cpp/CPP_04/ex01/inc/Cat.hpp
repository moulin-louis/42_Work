/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 11:51:11 by loumouli          #+#    #+#             */
/*   Updated: 2023/03/17 10:28:21 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef CAT_H
#define CAT_H

#include <iostream>
#include "Animal.hpp"
#include "Brain.hpp"

class	Cat: public Animal {
	private:
		Brain*	my_brain;
	public:
		Cat( void );
		Cat ( const Cat& );
		~Cat( void );
		void	makeSound( void ) const ;
		std::string& getType( void );
		virtual	Brain*	get_brain( void ) const;
		Cat&	operator=(const Cat& );
		void display_brain( void );
		void set_idea( int, std::string const& );
};

#endif