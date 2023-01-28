/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 14:42:42 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/20 11:45:54 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
class Contact
{
private:
	std::string first_name;
	std::string	last_name;
	std::string	nickname;
	std::string	phone_nbr;
	std::string	secret;
public:
	Contact( void );
	~Contact( void );
	std::string	get_first_name( void );
	std::string	get_last_name( void );
	std::string	get_nickname( void );
	std::string	get_phone_nbr( void );
	std::string	get_secret( void );
	void		set_contact( void );

};