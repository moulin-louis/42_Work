/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:21:49 by loumouli          #+#    #+#             */
/*   Updated: 2023/03/16 09:49:06 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>

class RPN {
	private:
		std::stack<int> stack;
	public:
		RPN( void );
		RPN( const RPN& );
		~RPN( void );
		RPN&	operator=( const RPN& );
		int		process_input( const std::string& );
		void	sub_stack( void );
		void	add_stack( void );
		void	div_stack( void );
		void	mul_stack( void );
		void display_stack( void );
};

#endif