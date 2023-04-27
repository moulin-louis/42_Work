/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 18:15:28 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/26 13:31:48 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAU_H
# define BUREAU_H

# include <iostream>
# include "Form.hpp"
class Form;

class Bureaucrat
{
private:
	const	std::string name;
	int		grade;
public:
	Bureaucrat( const std::string& name_input, const int grade_input );
	Bureaucrat( const Bureaucrat& );
	~Bureaucrat( void  );
	std::string	getName( void );
	int	getGrade( void );
	void	incrementGrade( void );
	void	decrementGrade( void );
	void	signForm( Form& );
	Bureaucrat&	operator=(const Bureaucrat& );

	//EXCEPTION CLASS
	class	GradeTooHighException: public std::exception {
	public:
		virtual const char* what( void ) const throw() {
			return ("Error: Grade is too high");
		}
	~GradeTooHighException() throw() {};
	};

	class GradeTooLowException: public std::exception {
	public:
		virtual const char* what( void ) const throw() {
			return ("Error: Grade is too low");
		}
		~GradeTooLowException() throw() {};
	};
};
std::ostream&	operator<<(std::ostream& os, Bureaucrat& var);
#endif