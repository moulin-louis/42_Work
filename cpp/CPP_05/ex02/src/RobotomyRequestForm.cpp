/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:09:42 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/27 12:49:58 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm( std::string target_input ) : AForm(72, 45, "RobotomyRequestForm")
{
	std::cout << "RobotomyRequestForm default constructor called" << std::endl;
	this->target = target_input;
	return ;
}

RobotomyRequestForm::RobotomyRequestForm( RobotomyRequestForm& var ) : AForm(var.get_grade_sig(), var.get_grade_exe(), var.get_name())
{
	std::cout << "RobotomyRequestForm constructor by copy called" << std::endl;
	this->target = var.target;
	return ;
}

RobotomyRequestForm::~RobotomyRequestForm( void )
{
	std::cout << "Presidential default destructor called" << std::endl;
	return ;
}

void	RobotomyRequestForm::execute( Bureaucrat const & executor ) const
{
	if (this->get_signed() == true && executor.getGrade() <= this->get_grade_exe())
	{
		std::srand((unsigned)time(NULL));
		int random_nbr = std::rand();
		std::cout << "BRRRR BRRRR BRRR" << std::endl;
		if (random_nbr % 2)
			std::cout << this->target << " has been robotomized !" << std::endl;
		else
			std::cout << "The robotomy failed..." << std::endl;
		return ;
	}
	throw AForm::GradeTooLowException();
}

void	RobotomyRequestForm::beSigned( Bureaucrat& var )
{
	if (var.getGrade() <= this->get_grade_sig())
	{
		std::cout << var.getName() << " signed RobotomyRequestForm for " << this->target << std::endl;
		this->change_sig();
		return;
	}
	throw AForm::GradeTooLowException();
}

RobotomyRequestForm& RobotomyRequestForm::operator=( const RobotomyRequestForm& var)
{
	std::cout << "RobotomyRequestForm assignation called" << std::endl;
	this->target = var.target;
	return (*this);
}