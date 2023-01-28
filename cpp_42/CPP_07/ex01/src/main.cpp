/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 18:08:04 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/27 18:17:52 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iter.h"

void	do_nothing( int a)
{
	std::cout << a << std::endl;
}

int	main( void )
{
	int *temp;
	temp = new int[7];
	temp[0] = 0;
	temp[1] = 1;
	temp[2] = 2;
	temp[3] = 3;
	temp[4] = 4;
	temp[5] = 5;
	temp[6] = 6;
	iter<int, int, void(int)>(temp, 7, do_nothing);
	delete[] temp;
	return (0);
}