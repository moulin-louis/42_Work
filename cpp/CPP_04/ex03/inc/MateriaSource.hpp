/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 17:41:23 by loumouli          #+#    #+#             */
/*   Updated: 2023/03/16 17:46:48 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef MATERIASOURCE_HPP
#define MATERIASOURCE_HPP

#include <iostream>
#include "IMateriaSource.hpp"

class MateriaSource : public IMateriaSource {
	private:
		AMateria **source;
		int		len_source;
	public:
		MateriaSource( void );
		MateriaSource( const MateriaSource& );
		MateriaSource& operator=( const MateriaSource& );
		virtual ~MateriaSource( void );
		virtual void learnMateria( AMateria* );
		virtual AMateria* createMateria( std::string const& );
};

#endif