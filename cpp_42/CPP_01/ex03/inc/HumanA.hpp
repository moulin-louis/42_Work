/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 13:33:10 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/20 12:44:49 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include "Weapon.hpp"

class HumanA
{
private:
	std::string	name;
	Weapon*	weapon;
public:
	HumanA( std::string, Weapon& weapon );
	~HumanA( void );
	void	attack( void );
};