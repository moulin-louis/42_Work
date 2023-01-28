/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 10:57:55 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/28 12:12:27 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef SPAN_HPP
#define SPAN_HPP

#include <iostream>
#include <vector>
#include <stdexcept>
#include<cstdlib>
#include <algorithm>
#include <numeric>
#include <functional>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <string_view>
#include <vector>


class Span
{
private:
	const unsigned int		max_val;
	unsigned int		crt_nbr_val;
	std::vector<int>	stock;
	Span( void );
public:
	Span( const unsigned int& max_input );
	Span( const Span& );
	~Span( void );
	Span&	operator=(const Span& );
	void	addNumber( const int& input );
	int		shortestSpan( void );
	int		longestSpan( void );
};
#endif