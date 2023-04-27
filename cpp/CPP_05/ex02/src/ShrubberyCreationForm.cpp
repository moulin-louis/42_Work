/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:09:44 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/27 12:53:07 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm( std::string target_input ) : AForm(145, 137, "ShrubberyCreationForm")
{
	std::cout << "ShrubberyCreationForm default constructor called" << std::endl;
	this->target = target_input;
	return ;
}

ShrubberyCreationForm::ShrubberyCreationForm( ShrubberyCreationForm& var ) : AForm(var.get_grade_sig(), var.get_grade_exe(), var.get_name())
{
	std::cout << "ShrubberyCreationForm constructor by copy called" << std::endl;
	this->target = var.target;
	return ;
}

ShrubberyCreationForm::~ShrubberyCreationForm( void )
{
	std::cout << "Presidential default destructor called" << std::endl;
	return ;
}

void	ShrubberyCreationForm::execute( Bureaucrat const & executor ) const
{
	if (this->get_signed() == true && executor.getGrade() <= this->get_grade_exe())
	{
		std::ofstream	outfile;
		std::string temp = this->target;
		temp += "_shrubery";
		outfile.open(temp.c_str(), std::ios::out | std::ios::trunc);
		if (!outfile.is_open())
		{
			std::cout << "failed to open outfile, try again" << std::endl;
			return ;
		}
		outfile << "*Some_sort_of_ascii_tree*";
		outfile.close();
		return ;
	}
	throw AForm::GradeTooLowException();
}

void	ShrubberyCreationForm::beSigned( Bureaucrat& var )
{
	if (var.getGrade() <= this->get_grade_sig())
	{
		std::cout << var.getName() << " signed ShrubberyCreationForm for " << this->target << std::endl;
		this->change_sig();
		return;
	}
	throw AForm::GradeTooLowException();
}

ShrubberyCreationForm& ShrubberyCreationForm::operator=( const ShrubberyCreationForm& var)
{
	std::cout << "ShrubberyCreationForm assignation called" << std::endl;
	this->target = var.target;
	return (*this);
}