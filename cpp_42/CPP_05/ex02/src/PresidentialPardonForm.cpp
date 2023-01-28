/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:09:39 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/27 12:49:56 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm( std::string target_input ) : AForm(25, 5, "PresidentialPardonForm")
{
	std::cout << "PresidentialPardonForm default constructor called" << std::endl;
	this->target = target_input;
	return ;
}

PresidentialPardonForm::PresidentialPardonForm( PresidentialPardonForm& var ) : AForm(var.get_grade_sig(), var.get_grade_exe(), var.get_name())
{
	std::cout << "PresidentialPardonForm constructor by copy called" << std::endl;
	this->target = var.target;
	return ;
}

PresidentialPardonForm::~PresidentialPardonForm( void )
{
	std::cout << "Presidential default destructor called" << std::endl;
	return ;
}

void	PresidentialPardonForm::execute( Bureaucrat const & executor ) const
{
	if (this->get_signed() == true && executor.getGrade() <= this->get_grade_exe())
	{
		std::cout << "Informs that " << this->target << " has been pardoned by Zaphod Beeblebrox." << std::endl;
		return ;
	}
	throw AForm::GradeTooLowException();
}

void	PresidentialPardonForm::beSigned( Bureaucrat& var )
{
	if (var.getGrade() <= this->get_grade_sig())
	{
		std::cout << var.getName() << " signed PresidentialPardonForm for " << this->target << std::endl;
		this->change_sig();
		return;
	}
	throw AForm::GradeTooLowException();
}

PresidentialPardonForm& PresidentialPardonForm::operator=( const PresidentialPardonForm& var)
{
	std::cout << "PresidentialPardonForm assignation called" << std::endl;
	this->target = var.target;
	return (*this);
}