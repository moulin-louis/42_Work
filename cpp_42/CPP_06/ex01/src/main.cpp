/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:26:25 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/27 17:39:30 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Data.hpp"
#include <stdint.h>

uintptr_t serialize( Data* ptr ) { return(reinterpret_cast<uintptr_t>(ptr)); }

Data*	deserialize( uintptr_t raw ) { return(reinterpret_cast<Data *>(raw)); }

int	main( void )
{
	Data temp;
	std::cout << std::endl;
	std::cout << "Address :\t\t" << &temp << std::endl;
	std::cout << "Deserialize :\t\t" << deserialize(serialize(&temp)) << std::endl;
	std::cout << std::endl;
}