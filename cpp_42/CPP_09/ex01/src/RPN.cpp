/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:25:50 by loumouli          #+#    #+#             */
/*   Updated: 2023/03/14 15:54:01 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN( void ) {
	return ;
}

RPN::RPN( const RPN& var ) {
	*this = var;
	return ;
}

RPN::~RPN( void ) {
	return ;
}

RPN& RPN::operator=( const RPN& var ) {
	this->stack = var.stack;
	return *this;
}

bool is_forbiden_char( char c ) {
	if (c == ' ') {
		return false;
	}
	if (c >= '0' && c <= '9') {
		return false;
	}
	if (c == '*' || c == '/' || c == '+' || c == '-' ) {
		return false;
	}
	return true;
}

void	RPN::add_stack( void ) {
	if (this->stack.size() != 2) {
		throw std::invalid_argument("invalid logic in input");
	}
	int two = this->stack.top();
	this->stack.pop();
	int one = this->stack.top();
	this->stack.pop();
	this->stack.push(one + two);
}

void	RPN::sub_stack( void ) {
	if (this->stack.size() != 2) {
		throw std::invalid_argument("invalid logic in input");
	}
	int two = this->stack.top();
	this->stack.pop();
	int one = this->stack.top();
	this->stack.pop();
	this->stack.push(one - two);
}

void	RPN::div_stack( void ) {
	if (this->stack.size() != 2) {
		throw std::invalid_argument("invalid logic in input");
	}
	int two = this->stack.top();
	this->stack.pop();
	int one = this->stack.top();
	this->stack.pop();
	this->stack.push(one / two);
}

void	RPN::mul_stack( void ) {
	if (this->stack.size() != 2) {
		throw std::invalid_argument("invalid logic in input");
	}
	int two = this->stack.top();
	this->stack.pop();
	int one = this->stack.top();
	this->stack.pop();
	this->stack.push(one * two);
}

int RPN::process_input( const std::string& input ) {
	if (input.empty()) {
		throw std::invalid_argument("Empty args");
	}
	for (std::string::const_iterator it = input.begin(); it != input.end(); it++) {
		if (is_forbiden_char(*it)) {
			throw std::invalid_argument("Invalid character");
		}
	}
	for (unsigned long i = 0; i < input.size(); i++)
	{
		if (input[i] == ' ') { continue; }
		else if (input[i] == '-') {	this->sub_stack(); }
		else if (input[i] == '+') { this->add_stack(); }
		else if (input[i] == '/') { this->div_stack(); }
		else if (input[i] == '*') { this->mul_stack(); }
		else { this->stack.push(input[i] - '0'); }
	}
	if (this->stack.size() != 1 ) {
		throw std::invalid_argument("invalid logic in input");
	}
	std::cout << this->stack.top() << std::endl;
	return (0);
}