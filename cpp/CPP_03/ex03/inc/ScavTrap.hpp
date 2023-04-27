/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:34:05 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/20 19:09:18 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "ClapTrap.hpp"
class ScavTrap : virtual public ClapTrap
{
public:
	ScavTrap( void );
	ScavTrap( const std::string& );
	ScavTrap(const ScavTrap&);
	~ScavTrap();
	void	attack(const std::string& target);
	void	guardGate( void );
	ScavTrap& operator=(const ScavTrap&);
};
