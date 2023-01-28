/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:45:56 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/20 15:34:27 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>

class	ClapTrap
{
protected:
	std::string	name;
	int		hit_point;
	int		energy_point;
	int		attack_dmg;
public:
	ClapTrap( void );
	ClapTrap( const ClapTrap& );
	ClapTrap( std::string name );
	~ClapTrap( void );
	void	attack(const std::string& target);
	void	takeDamage(unsigned int amout);
	void	beRepaired(unsigned int amount);
	void	setDamage( int amount );
	int		get_dmg( void ) ;
	ClapTrap& operator=(const ClapTrap&);
};