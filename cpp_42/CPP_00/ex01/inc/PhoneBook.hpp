/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 14:42:45 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/20 12:23:35 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Contact.hpp"
#include <cstdlib>
#include <limits>

class PhoneBook
{
private:
	int	nbr_of_contact;
	Contact	book[8];
public:
	PhoneBook( void );
	~PhoneBook();
	void	add_contact( PhoneBook *var );
	void	search_contact( PhoneBook *var);
};