/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:01:05 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/26 13:58:54 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"

Form::Form( void ) : name("PLACEHOLDER"), grade_req_sig(0), grade_req_exe(0)
{
	std::cout << "Form default contructor called" << std::endl;
	return ;
}

Form::Form(const int grade_sig_input, const int grade_exe_input, const std::string name_input) : name(name_input), grade_req_sig(grade_sig_input), grade_req_exe(grade_exe_input)
{
	if (grade_sig_input < 1 || grade_exe_input < 1)
		throw GradeTooHighException();
	else if (grade_sig_input > 150 || grade_exe_input > 150)
		throw GradeTooLowException();
	else
	{
		std::cout << "Form constructor with args called" << std::endl;
		this->is_signed = false;
		return ;
	}
}

Form::Form( const Form& var) : name(var.name), grade_req_sig(var.grade_req_sig), grade_req_exe(var.grade_req_exe)
{
	this->is_signed = false;
	std::cout << "Form constructor by copy called" << std::endl;
	return ;
}

Form::~Form( void )
{
	std::cout << "Form default destructor called" << std::endl;
	return ;
}

int	Form::get_grade_sig( void ) { return(this->grade_req_sig); }
int	Form::get_grade_exe( void ) { return(this->grade_req_exe); }
bool	Form::get_signed( void ) { return(this->is_signed); }
std::string	Form::get_name( void ) { return(this->name); }

void	Form::beSigned( Bureaucrat& var )
{
	if (var.getGrade() > this->grade_req_sig)
		throw GradeTooLowException();
	else
		this->is_signed = true;
}

Form&	Form::operator=( const Form& var )
{
	(void)var;
	std::cout << "cant do anything cause all attributes are const" << std::endl;
	return (*this);
}

std::ostream&	operator<<( std::ostream& os, Form& var)
{
	os << "Form: " << var.get_name() << ", grade_req_sig: " << var.get_grade_sig();
	os << ", grade_req_exe: " << var.get_grade_exe() << ", is_signed: " << var.get_signed();
	return (os);
}