/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 13:26:47 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/23 13:37:08 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef WRONGANIMAL_H
#define WRONGANIMAL_H
#include <iostream>

class	WrongAnimal
{
protected:
	std::string type;
public:
	WrongAnimal( void );
	WrongAnimal( const WrongAnimal& );
	virtual ~WrongAnimal( void );
	void makeSound( void ) const;
	std::string getType( void )  const;
	WrongAnimal& operator=( const WrongAnimal& );
};
#endif