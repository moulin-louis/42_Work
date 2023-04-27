/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 17:09:29 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/20 12:58:50 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

Harl::Harl( void )
{
	init();
	std::cout << "Harl constructor called" << std::endl;
	return ;
}

Harl::~Harl( void )
{
	std::cout << "Harl destructor called" << std::endl;
	return ;
}

void	Harl::init( void )
{
	this->array[0].name = "DEBUG";
	this->array[0].ptr = &Harl::debug;
	this->array[1].name = "INFO";
	this->array[1].ptr = &Harl::info;
	this->array[2].name = "WARNING";
	this->array[2].ptr = &Harl::warning;
	this->array[3].name = "ERROR";
	this->array[3].ptr = &Harl::error;
}

void	Harl::debug( void )
{
	std::cout << "I love having extra bacon for my 7XL-double-cheese-triple-pickle-specialketchup burger. I really do!";
	std::cout << std::endl;
}

void	Harl::info( void )
{
	std::cout << "I cannot believe adding extra bacon costs more money. You didn’t put enough bacon in my burger! If you did, I wouldn’t be asking for more!";
	std::cout << std::endl;
}

void	Harl::warning( void )
{
	std::cout << "I think I deserve to have some extra bacon for free. I’ve been coming for years whereas you started working here since last month.";
	std::cout << std::endl;
}

void	Harl::error( void )
{
	std::cout << "This is unacceptable! I want to speak to the manager now.";
	std::cout << std::endl;
}

void	Harl::complain( std::string level )
{
	for (int i = 0; i < 4; i++)
	{
		if (level == this->array[i].name)
		{
			(this->*array[i].ptr)();
			return ;
		}
	}
}
