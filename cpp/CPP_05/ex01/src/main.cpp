/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 18:15:00 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/26 13:57:50 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Form.hpp"

int	main( void )
{
	//Try a form the worker can sign

	Form* form1_ptr;
	try {
		form1_ptr = new Form(50, 50, "AC36");
	}
	catch (Form::GradeTooHighException& mce)
	{
		std::cout << "Trying to create an instance of Form:" << std::endl << mce.what() << std::endl;
		return 1;
	}
	catch (Form::GradeTooLowException& mce)
	{
		std::cout << "Trying to create an instance of Form:" << std::endl << mce.what() << std::endl;
		return 1;
	}
	Bureaucrat worker1("Worker1", 50);
	std::cout << *form1_ptr << std::endl << std::endl;
	worker1.signForm(*form1_ptr);
	std::cout << *form1_ptr << std::endl;
	delete form1_ptr;

	//Test a form that the worker cant sign

	// Form* form1_ptr;
	// try {
	// 	form1_ptr = new Form(50, 50, "AC36");
	// }
	// catch (Form::GradeTooHighException& mce)
	// {
	// 	std::cout << "Trying to create an instance of Form:" << std::endl << mce.what() << std::endl;
	// 	return 1;
	// }
	// catch (Form::GradeTooLowException& mce)
	// {
	// 	std::cout << "Trying to create an instance of Form:" << std::endl << mce.what() << std::endl;
	// 	return 1;
	// }
	// Bureaucrat worker1("Worker1", 51);
	// std::cout << *form1_ptr << std::endl << std::endl;
	// worker1.signForm(*form1_ptr);
	// std::cout << *form1_ptr << std::endl;

	//Test a invalid form

	// Form* form1_ptr;
	// try {
	// 	form1_ptr = new Form(3432, 50, "AC36");
	// }
	// catch (Form::GradeTooHighException& mce)
	// {
	// 	std::cout << "Trying to create an instance of Form:" << std::endl << mce.what() << std::endl;
	// 	return 1;
	// }
	// catch (Form::GradeTooLowException& mce)
	// {
	// 	std::cout << "Trying to create an instance of Form:" << std::endl << mce.what() << std::endl;
	// 	return 1;
	// }
	// Bureaucrat worker1("Worker1", 50);
	// std::cout << *form1_ptr << std::endl << std::endl;
	// worker1.signForm(*form1_ptr);
	// std::cout << *form1_ptr << std::endl;

	//Test and invalid form
	// Form* form1_ptr;
	// try {
	// 	form1_ptr = new Form(-1, 50, "AC36");
	// }
	// catch (Form::GradeTooHighException& mce)
	// {
	// 	std::cout << "Trying to create an instance of Form:" << std::endl << mce.what() << std::endl;
	// 	return 1;
	// }
	// catch (Form::GradeTooLowException& mce)
	// {
	// 	std::cout << "Trying to create an instance of Form:" << std::endl << mce.what() << std::endl;
	// 	return 1;
	// }
	// Bureaucrat worker1("Worker1", 50);
	// std::cout << *form1_ptr << std::endl << std::endl;
	// worker1.signForm(*form1_ptr);
	// std::cout << *form1_ptr << std::endl;
}