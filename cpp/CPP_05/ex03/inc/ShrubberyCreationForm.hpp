/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:22:01 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/27 12:53:23 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef SHRUB_H
#define SHRUB_H

#include "AForm.hpp"
#include <fstream>
class ShrubberyCreationForm : public AForm
{
private:
	std::string target;
public:
	ShrubberyCreationForm( std::string target_input );
	ShrubberyCreationForm( ShrubberyCreationForm& );
	~ShrubberyCreationForm( void );
	void	execute( Bureaucrat const & executor ) const ;
	void	beSigned( Bureaucrat& );
	ShrubberyCreationForm& operator=( const ShrubberyCreationForm& );
};

#endif