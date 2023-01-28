/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 18:15:00 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/27 12:54:20 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "AForm.hpp"

int	main( void )
{
	// Bureaucrat worker1("Worker1", 45);
	// RobotomyRequestForm	form1("Louis");
	// std::cout << std::endl;
	// try {
	// 	form1.beSigned(worker1);
	// }
	// catch (AForm::GradeTooLowException& mce)
	// {
	// 	std::cout << "Error signing " << form1.get_name() << std::endl << mce.what() << std::endl;
	// 	return (1);
	// }
	// worker1.executeForm(form1);
	// std::cout << std::endl;

		
	// Bureaucrat worker1("Worker1", 80);
	// RobotomyRequestForm	form1("Louis");
	// std::cout << std::endl;
	// try {
	// 	form1.beSigned(worker1);
	// }
	// catch (AForm::GradeTooLowException& mce)
	// {
	// 	std::cout << "Error signing " << form1.get_name() << std::endl << mce.what() << std::endl;
	// 	return (1);
	// }
	// worker1.executeForm(form1);
	// std::cout << std::endl;


	// Bureaucrat worker1("Worker1", 50);
	// RobotomyRequestForm	form1("Louis");
	// std::cout << std::endl;
	// try {
	// 	form1.beSigned(worker1);
	// }
	// catch (AForm::GradeTooLowException& mce)
	// {
	// 	std::cout << "Error signing " << form1.get_name() << std::endl << mce.what() << std::endl;
	// 	return (1);
	// }
	// worker1.executeForm(form1);
	// std::cout << std::endl;


	// Bureaucrat worker1("Worker1", 1);
	// Bureaucrat	worker2("Worker2", 70);
	// RobotomyRequestForm	form1("Louis");
	// std::cout << std::endl;
	// try {
	// 	form1.beSigned(worker2);
	// }
	// catch (AForm::GradeTooLowException& mce)
	// {
	// 	std::cout << "Error signing " << form1.get_name() << std::endl << mce.what() << std::endl;
	// 	return (1);
	// }
	// worker1.executeForm(form1);
	// std::cout << std::endl;


	// Bureaucrat* ptr1;
	// try {
	// 	ptr1 = new Bureaucrat("Worker1", 300);
	// }
	// catch (Bureaucrat::GradeTooLowException& mce)
	// {
	// 	std::cout << "Error creating instance of bureacrat" << std::endl << mce.what() << std::endl;
	// 	return 1;
	// }
	// catch (Bureaucrat::GradeTooHighException& mce)
	// {
	// 	std::cout << "Error creating instance of bureacrat" << std::endl << mce.what() << std::endl;
	// 	return 1;
	// }
	// delete ptr1;


	Bureaucrat worker1("Worker1", 1);
	ShrubberyCreationForm	form1("Louis");
	std::cout << std::endl;
	try {
		form1.beSigned(worker1);
	}
	catch (AForm::GradeTooLowException& mce)
	{
		std::cout << "Error signing " << form1.get_name() << std::endl << mce.what() << std::endl;
		return (1);
	}
	worker1.executeForm(form1);
	std::cout << std::endl;
}