/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:57:09 by loumouli          #+#    #+#             */
/*   Updated: 2023/03/16 16:41:55 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef AMATERIA_H
#define AMATERIA_h

#include <iostream>
#include "ICharacter.hpp"
class ICharacter;

class AMateria
{
protected:
	std::string type;
public:
	AMateria( void );
	AMateria( const AMateria& );
	AMateria( std::string const& );
	virtual ~AMateria( void );
	AMateria& operator=( const AMateria& );
	std::string const& getType( void ) const;
	virtual AMateria* clone( void ) const = 0;
	virtual void use( ICharacter& );
};

#endif