/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 13:08:25 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/29 15:20:06 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"

Intern::Intern( void )
{
	std::cout << "Intern default constructor called" << std::endl;
	return ;
}

Intern::Intern( const Intern& var )
{
	(void)var;
	//std::cout << "Intern constructor by copy called" << std::endl;
	return ;
}

Intern::~Intern( void )
{
	std::cout << "Intern default destructor called" << std::endl;
	return ;
}

AForm*	Intern::makeForm( const std::string& form_name, const std::string& target )
{
	AForm*	result;
	sarr_form forms[] = 
	{
		{ "presidential pardon", new PresidentialPardonForm(target) },
		{ "robotomy request", new RobotomyRequestForm(target) },
		{ "shrubbery creation", new ShrubberyCreationForm(target) },
		{ "", NULL }
	};
	for (int i = 0; i < 4; i ++) {
		if (form_name.compare(forms[i].formName) == 0)
		{
		std::cout << "Intern creates " << forms[i].formName << std::endl;
			result = forms[i].formType;
		}
		else
			delete forms[i].formType;	
	}
	return (result);
}

Intern&	Intern::operator=( const Intern& var )
{
	(void)var;
	return (*this);
}