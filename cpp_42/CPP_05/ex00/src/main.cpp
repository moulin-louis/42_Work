/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 18:15:00 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/26 12:48:15 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

int	main( void )
{
	//Creating temp1 instance, trying to catch any error
	Bureaucrat* temp1;
	try {
		temp1 = new Bureaucrat("Worker1", 1);
	}
	catch (Bureaucrat::GradeTooHighException& mce)
	{
		std::cout << "Trying to create instance : ";
		std::cout << mce.what() << std::endl;
		return 1;
	}
	catch (Bureaucrat::GradeTooLowException& mce)
	{
		std::cout << "Trying to create instance : ";
		std::cout << mce.what() << std::endl; 
		return 1;
	}

	//Creating temp2 instance, trying to catch any error
	Bureaucrat* temp2;
	try {
		temp2 = new Bureaucrat("Worker1", 150);
	}
	catch (Bureaucrat::GradeTooHighException& mce)
	{
		std::cout << "Trying to create instance : ";
		std::cout << mce.what() << std::endl;
		delete temp1;
		return 1;
	}
	catch (Bureaucrat::GradeTooLowException& mce)
	{
		std::cout << "Trying to create instance : ";
		std::cout << mce.what() << std::endl; 
		delete temp1;
		return 1;
	}

	//Trying to increment and decrement temp1 grade, catching every error
	std::cout << *temp1 << std::endl;
	try {
		temp1->incrementGrade();
	}
	catch (Bureaucrat::GradeTooHighException& mce) {
		std::cout << "Trying to increment : ";
		std::cout << mce.what() << std::endl;
	}
	try {
		temp1->decrementGrade();
	}
	catch (Bureaucrat::GradeTooLowException& mce) {
		std::cout << "Trying to decrement : ";
		std::cout << mce.what() << std::endl;
	}
	std::cout << *temp1 << std::endl;

	std::cout << std::endl;

	//Trying to increment and decrement temp2 grade, catching every error
	std::cout << *temp2 << std::endl;
	try {
		temp2->decrementGrade();
	}
	catch (Bureaucrat::GradeTooLowException& mce) {
		std::cout << "Trying to decrement : ";
		std::cout << mce.what() << std::endl;
	}
	try {
		temp2->incrementGrade();
	}
	catch (Bureaucrat::GradeTooHighException& mce) {
		std::cout << "Trying to increment : ";
		std::cout << mce.what() << std::endl;
	}
	std::cout << *temp2 << std::endl;

	//Releasing allocated memory
	delete temp1;
	delete temp2;
}