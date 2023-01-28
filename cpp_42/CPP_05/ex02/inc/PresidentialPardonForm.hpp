/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:27:20 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/27 12:23:58 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef PRESID_H
#define PRESID_H

#include "AForm.hpp"
class PresidentialPardonForm : public AForm
{
private:
	std::string	target;
public:
	PresidentialPardonForm( std::string target );
	PresidentialPardonForm( PresidentialPardonForm& );
	~PresidentialPardonForm( void );
	void	execute( Bureaucrat const & executor ) const ;
	void	beSigned( Bureaucrat& );
	PresidentialPardonForm&	operator=(const PresidentialPardonForm& );
};
#endif