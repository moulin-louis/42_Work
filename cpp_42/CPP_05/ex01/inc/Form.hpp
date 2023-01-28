/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:51:46 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/26 13:32:41 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORM_H
# define FORM_H

# include <iostream>
# include "Bureaucrat.hpp"
class Bureaucrat;

class	Form
{
private:
	const	std::string name;
	bool	is_signed;
	const	int	grade_req_sig;
	const	int	grade_req_exe;
	Form( void );
public:
	Form(const int grad_sig_input, const int grad_exe_input, const std::string name_input);
	Form( const Form& );
	~Form( void );
	int		get_grade_sig( void );
	int		get_grade_exe( void );
	bool	get_signed( void );
	std::string	get_name( void );
	void	beSigned( Bureaucrat& );
	Form& operator=(const Form& );
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
std::ostream&	operator<<( std::ostream& os, Form& );
#endif