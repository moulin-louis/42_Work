/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 13:42:06 by loumouli          #+#    #+#             */
/*   Updated: 2023/03/17 10:25:24 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef BRAIN_H
#define BRAIN_H

#include <iostream>

class Brain {
	public:
		std::string	ideas[100];
		Brain( void );
		Brain( const Brain&);
		~Brain( void );
		Brain&	operator=(const Brain& );
		void display_brain( void );
		void set_idea( int, std::string const& );
};

#endif