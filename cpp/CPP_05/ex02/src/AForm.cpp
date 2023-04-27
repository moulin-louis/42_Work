/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:01:05 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/27 12:17:43 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"

AForm::AForm( void ) : name("PLACEHOLDER"), grade_req_sig(0), grade_req_exe(0)
{
	std::cout << "AForm default contructor called" << std::endl;
	return ;
}

AForm::AForm(const int grade_sig_input, const int grade_exe_input, const std::string name_input) : name(name_input), grade_req_sig(grade_sig_input), grade_req_exe(grade_exe_input)
{
	if (grade_sig_input < 1 || grade_exe_input < 1)
		throw GradeTooHighException();
	else if (grade_sig_input > 150 || grade_exe_input > 150)
		throw GradeTooLowException();
	else
	{
		std::cout << "AForm constructor with args called" << std::endl;
		this->is_signed = false;
		return ;
	}
}

AForm::AForm( const AForm& var) : name(var.name), grade_req_sig(var.grade_req_sig), grade_req_exe(var.grade_req_exe)
{
	this->is_signed = false;
	std::cout << "AForm constructor by copy called" << std::endl;
	return ;
}

AForm::~AForm( void )
{
	std::cout << "AForm default destructor called" << std::endl;
	return ;
}

int	AForm::get_grade_sig( void ) const { return(this->grade_req_sig); }
int	AForm::get_grade_exe( void ) const { return(this->grade_req_exe); }
bool	AForm::get_signed( void ) const { return(this->is_signed); }
std::string	AForm::get_name( void ) const { return(this->name); }

void	AForm::change_sig( void )
{
	this->is_signed = true;
	return ;
}

AForm&	AForm::operator=( const AForm& var )
{
	(void)var;
	std::cout << "cant do anything cause all attributes are const" << std::endl;
	return (*this);
}

std::ostream&	operator<<( std::ostream& os, AForm& var)
{
	os << "AForm: " << var.get_name() << ", grade_req_sig: " << var.get_grade_sig();
	os << ", grade_req_exe: " << var.get_grade_exe() << ", is_signed: " << var.get_signed();
	return (os);
}