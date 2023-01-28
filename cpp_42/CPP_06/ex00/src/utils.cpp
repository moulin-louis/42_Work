/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 14:28:06 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/27 16:38:01 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Conversion.hpp"

bool atoi_char(int* val, const std::string& str )
{
    std::string::const_iterator it;
    it = str.begin();
    bool isPositive = true;
    if ( *it=='-' ) {
        isPositive = false;
        ++it;
    }
    while ( *it ) {
		int i = 0;
		int nbr2 = *val;
		while(i++ < 9)
		{
			int	nbr_tmp;
			nbr_tmp = *val;
			*val += nbr2;
			if (*val < nbr_tmp)
			{
 				throw std::invalid_argument("impossible");
			}
		}
		*val = *val + (*it)-'0';
		++it;
    }
	*val = isPositive ? *val : -(*val);
    return (true);
}

bool atoi_int(int* val, const std::string& str )
{
	long result = 0;
    std::string::const_iterator it;
    it = str.begin();
    bool isPositive = true;
    if ( *it=='-' ) {
        isPositive = false;
        ++it;
    }
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
	result = isPositive ? result : -result;
	if (result < -2147483648 || result > 2147483647)
 		throw std::invalid_argument("overflow");
	*val = result;
    return (true);
}