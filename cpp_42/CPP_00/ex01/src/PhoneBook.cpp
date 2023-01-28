/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 15:25:18 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/20 12:23:34 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

PhoneBook::PhoneBook ( void )
{
	std::cout << "\e[1;36m" << "- PhoneBook constructor called" << "\e[0m" << std::endl;
	this->nbr_of_contact = 0;
	return ;
}

PhoneBook::~PhoneBook ( void )
{
	std::cout << "\e[1;34m" << "- Phonebook destructor called" << "\e[0m" << std::endl;
	return ;
}

void	PhoneBook::add_contact( PhoneBook *var )
{
	static int i;
	var->book[i].set_contact();
	i++;
	if (i == 8)
		i = 0;
	if (var->nbr_of_contact < 8)
		var->nbr_of_contact++;
	return ;
}

void	put_space(const std::string &str)
{
	if (str.length() < 10)
	{
		int x = 10 - str.length();
		while (x--)
			std::cout << " ";
	}
	return ;
}

void	PhoneBook::search_contact( PhoneBook *var )
{
	for (int i = 0; i < var->nbr_of_contact; i++)
	{
		std::cout << i << "         " << "|";
		
		std::cout << var->book[i].get_first_name().substr(0, 9);
		if (var->book[i].get_first_name().length() >= 10)
			std::cout << ".";
		put_space(var->book[i].get_first_name());
		std::cout << "|";

		std::cout << var->book[i].get_last_name().substr(0, 9);
		if (var->book[i].get_last_name().length() >= 10)
			std::cout << ".";
		put_space(var->book[i].get_last_name());
		std::cout << "|";

		std::cout << var->book[i].get_nickname().substr(0, 9);
		if (var->book[i].get_nickname().length() >= 10)
			std::cout << ".";
		put_space(var->book[i].get_nickname());
		std::cout << std::endl;
	}
	if (var->nbr_of_contact == 0)
		return ;
	std::cout << "Which ID to you want to see ?" << std::endl;
	int	input;
	std::cin >> input;
	if (std::cin.fail())
	{
		if (std::cin.eof())
			return ;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return ;
	}
	if (input < 0 || input > var->nbr_of_contact)
	{
		std::cout << "Wrong index" << std::endl;
		return ;
	}
	std::cout << var->book[input].get_first_name() << std::endl;
	std::cout << var->book[input].get_last_name() << std::endl;
	std::cout << var->book[input].get_nickname() << std::endl;
	std::cout << var->book[input].get_phone_nbr() << std::endl;
	std::cout << var->book[input].get_secret() << std::endl;
	
}