/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:51:46 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/27 12:18:04 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AFORM_H
# define AFORM_H

# include <iostream>
# include "Bureaucrat.hpp"
class Bureaucrat;

class	AForm
{
private:
	const	std::string name;
	bool	is_signed;
	const	int	grade_req_sig;
	const	int	grade_req_exe;
	AForm( void );
public:
	AForm(const int grad_sig_input, const int grad_exe_input, const std::string name_input);
	AForm( const AForm& );
	virtual ~AForm( void );
	int		get_grade_sig( void ) const ;
	int		get_grade_exe( void ) const ;
	bool	get_signed( void ) const ;
	std::string	get_name( void ) const ;
	void	change_sig( void );
	virtual void	beSigned( Bureaucrat& ) = 0;
	virtual	void	execute( Bureaucrat const & executor ) const = 0;
	AForm& operator=(const AForm& );
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
std::ostream&	operator<<( std::ostream& os, AForm& );
#endif