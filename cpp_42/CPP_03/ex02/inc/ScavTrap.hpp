/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:34:05 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/20 18:13:56 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "ClapTrap.hpp"
class ScavTrap : public ClapTrap
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
