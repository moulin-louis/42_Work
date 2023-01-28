/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 18:31:28 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/26 12:48:38 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat( const std::string& name_input, const int grade_input ) : name(name_input)
{
	if (grade_input < 1)
	{
		throw GradeTooHighException();
		return ;
	}
	if (grade_input > 150)
	{
		throw GradeTooLowException();
		return ;
	}
	else
	{
		this->grade = grade_input;
		std::cout << "Bureaucrat default constructor called" << std::endl;
		return ;
	}
}

Bureaucrat::Bureaucrat( const Bureaucrat& var )
{
	this->grade = var.grade;
	std::cout << "Bureaucrat constructor by copy called" << std::endl;
	return ;
}

Bureaucrat::~Bureaucrat( void )
{
	std::cout << "Bureaucrat default destructor called" << std::endl;
	return ;
}

int	Bureaucrat::getGrade( void ) { return(this->grade); }
std::string	Bureaucrat::getName( void ) { return(this->name); }

void	Bureaucrat::incrementGrade( void )
{
	if (this->getGrade() == 1)
		throw GradeTooHighException();
	else
		this->grade--;
	return ;
}

void	Bureaucrat::decrementGrade( void )
{
	if (this->grade == 150)
		throw GradeTooLowException();
	else
		this->grade++;
	return ;
}

const char* what( void ) { return("Grad to low"); 	}

Bureaucrat& Bureaucrat::operator=( const Bureaucrat& var )
{
	this->grade = var.grade;
	std::cout << "Bureaucrat assignation called" << std::endl;
	return (*this);
}

std::ostream& operator<<( std::ostream& os,  Bureaucrat& var )
{
	os << var.getName() << " grade is " << var.getGrade();
	return (os);
}