/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:25:54 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/27 12:38:55 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef ROBOT_H
#define ROBOT_H

#include "AForm.hpp"
#include<cstdlib>
class RobotomyRequestForm : public AForm
{
private:
	std::string target;
public:
	RobotomyRequestForm( std::string target );
	RobotomyRequestForm( RobotomyRequestForm& );
	~RobotomyRequestForm( void );
	void	execute( Bureaucrat const & executor ) const ;
	void	beSigned( Bureaucrat& );
	RobotomyRequestForm&	operator=( const RobotomyRequestForm& );
};
#endif