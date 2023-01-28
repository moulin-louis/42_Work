/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 13:41:26 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/20 12:44:42 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Weapon.hpp"
#include <iostream>

class HumanB
{
private:
	std::string	name;
	Weapon* weapon;
public:
	HumanB( std::string name, Weapon& weapon );
	HumanB( std::string name );
	~HumanB( void );
	void	attack( void );
	void	setWeapon( Weapon& weapon );
};