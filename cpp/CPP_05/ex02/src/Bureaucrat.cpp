/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 18:31:28 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/27 12:49:34 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat( const std::string& name_input, const int grade_input ) : name(name_input)
{
	if (grade_input < 1)
		throw GradeTooHighException();
	if (grade_input > 150)
		throw GradeTooLowException();
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

int	Bureaucrat::getGrade( void ) const { return(this->grade); }
std::string	Bureaucrat::getName( void ) const { return(this->name); }

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

void	Bureaucrat::signForm( AForm& var )
{
	try {
		var.beSigned(*this);
	}
	catch (AForm::GradeTooLowException& mce)
	{
		std::cout << this->name << " couldnt sign " << var << " because :" << std::endl << mce.what() << std::endl;
		return ;
	}
	std::cout << this->name << " signed " << "Aform " <<  var.get_name() << std::endl;
}

void	Bureaucrat::executeForm( AForm const & form )
{
	try {
		form.execute(*this);
	}
	catch (AForm::GradeTooLowException& mce)
	{
		std::cout << "Cant execute form cause " << mce.what() << std::endl;
		return ;
	}
	std::cout << this->getName() << " executed " << form.get_name() << std::endl;
	return ;
}

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