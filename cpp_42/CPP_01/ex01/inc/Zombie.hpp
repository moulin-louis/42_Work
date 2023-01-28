/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 19:26:45 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/20 12:40:57 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
class	Zombie
{
private:
	std::string	name;
public:
	Zombie( std::string name );
	Zombie( void );
	~Zombie( void );
	void	announce( void );
	void	name_it(std::string name );
};

void	randomChump( std::string name );
Zombie* newZombie( std::string name );
Zombie* zombieHorde( int N, std::string name );