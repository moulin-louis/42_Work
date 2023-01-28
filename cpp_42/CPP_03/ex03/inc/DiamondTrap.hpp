/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 18:52:21 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/20 19:27:52 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "FragTrap.hpp"
#include "ScavTrap.hpp"

class	DiamondTrap: virtual public FragTrap, virtual public ScavTrap
{
private:
	std::string name;
public:
	DiamondTrap( void );
	DiamondTrap( const std::string& input );
	DiamondTrap( const DiamondTrap& );
	~DiamondTrap( void );
	void	whoAmI( void );
	int		get_dmg( void );
	int		get_energy( void );
	int		get_hit( void );
	DiamondTrap& operator=(const DiamondTrap& );
	using ScavTrap::attack;
};