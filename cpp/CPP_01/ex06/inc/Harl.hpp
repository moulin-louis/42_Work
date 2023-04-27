/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 17:06:50 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/20 13:38:54 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>

class Harl
{
typedef	struct	s_ptr_arr
{
	std::string	name;
	void(Harl::*ptr)(void);
}				ptr_arr;
private:
	void debug( void );
	void info( void );
	void warning( void );
	void error( void );
	void init( void );
	ptr_arr	array[4];
public:
	Harl( void );
	~Harl( void );
	void complain( std::string level );
};
