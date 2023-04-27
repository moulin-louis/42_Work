/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:27:31 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/27 17:30:06 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef DATA_H
#define DATA_H

#include <iostream>
class Data
{
private:
	int	value;
public:
	Data( void );
	Data( const Data& );
	~Data( void );
	Data&	operator=(const Data& );
};
#endif