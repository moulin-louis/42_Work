/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:47:27 by loumouli          #+#    #+#             */
/*   Updated: 2023/03/14 16:47:43 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

void atoi_int( unsigned int * val, const std::string& str ) {
	
	long result = 0;
    std::string::const_iterator it;
    it = str.begin();
    while ( *it && std::isdigit(*it)) {
		int i = 0;
		int nbr2 = result;
		int	nbr_tmp;
		while(i++ < 9)
		{
			nbr_tmp = result;
			result += nbr2;
			if (result < nbr_tmp)
 				throw std::invalid_argument("overflow");
		}
		nbr_tmp = result;
		result = result + ((*it)-'0');
		if (result < nbr_tmp)
			throw std::invalid_argument("overflow");
		++it;
    }
	if (result < -2147483648 || result > 2147483647)
 		throw std::invalid_argument("overflow");
	*val = result;
}
