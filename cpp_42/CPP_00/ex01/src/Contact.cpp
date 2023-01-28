/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 15:25:15 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/20 11:50:02 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

Contact::Contact ( void )
{
	std::cout << "\e[1;92m" << "- Contact constructor called" << "\e[0m" << std::endl;
	return ;
}

Contact::~Contact ( void )
{
	std::cout << "\e[1;91m" << "- Contact destructor called" << "\e[0m" << std::endl;
	return ;
}


std::string	Contact::get_first_name( void ) { return (this->first_name); }

std::string	Contact::get_last_name( void ) { return (this->last_name); }

std::string	Contact::get_nickname( void ) { return (this->nickname); }

std::string	Contact::get_phone_nbr( void ) { return (this->phone_nbr); }

std::string	Contact::get_secret( void ) { return (this->secret); }

void	Contact::set_contact( void )
{
	std::string	u_input;

	std::cout << "- Type is first name" << std::endl;
	std::cin >> u_input;
	this->first_name = u_input;

	std::cout << "- Type is last name" << std::endl;
	std::cin >> u_input;
	this->last_name = u_input;

	std::cout << "- Type is nickname" << std::endl;
	std::cin >> u_input;
	this->nickname = u_input;

	std::cout << "- Type is phone number" << std::endl;
	std::cin >> u_input;
	this->phone_nbr = u_input;
	
	std::cout << "- Type is darkest secret" << std::endl;
	std::cin >> u_input;
	this->secret = u_input;
}