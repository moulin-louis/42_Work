/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zombieHorde.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 12:10:00 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/20 12:43:44 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie* zombieHorde( int N, std::string name )
{
	Zombie* result;
	result = new Zombie[N];
	for (int ite = 0; ite < N; ite++)
	{
		result[ite].name_it(name);
		result[ite].announce();
	}
	return (result);
}