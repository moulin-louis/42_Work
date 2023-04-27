/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 13:25:11 by loumouli          #+#    #+#             */
/*   Updated: 2023/03/17 10:16:35 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef WRONGCAT_H
#define WRONGCAT_H

#include "WrongAnimal.hpp"

class	WrongCat: public WrongAnimal {
	public:
		WrongCat( void );
		WrongCat ( const WrongCat& );
		~WrongCat( void );
		void	makeSound( void ) const ;
		WrongCat&	operator=(const WrongCat& );
		std::string& getType( void );
};

#endif