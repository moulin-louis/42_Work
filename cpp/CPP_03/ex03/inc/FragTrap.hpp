/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 18:34:49 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/20 19:09:15 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "ClapTrap.hpp"

class	FragTrap: virtual public ClapTrap
{
public:
	FragTrap( void );
	FragTrap( const std::string& input );
	FragTrap( const FragTrap& );
	~FragTrap( void );
	FragTrap& operator=(const FragTrap& );
	void	highFivesGuys( void );
	
};