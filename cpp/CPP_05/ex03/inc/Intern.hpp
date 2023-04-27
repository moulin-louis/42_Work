/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 11:56:26 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/29 15:07:57 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef INTER_N
#define INTER_N

#include "AForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"
class Intern
{
public:
	Intern( void );
	Intern( const Intern& );
	~Intern( void );
	AForm*	makeForm( const std::string& form_name, const std::string& target);
	Intern&	operator=( const Intern& );
	typedef struct	sarr_form {
		std::string	formName;
		AForm		*formType;
	} arr_form;
};
#endif